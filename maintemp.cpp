#include "maintemp.h"
#include "ui_maintemp.h"
#include "cpustatus.h"
#include "gpustatus.h"
#include "memorystatus.h"
#include <sensors/sensors.h>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

MainTemp::MainTemp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainTemp)
{
    ui->setupUi(this);
    createStatuses();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGui()));
    timer->start(500);
}

MainTemp::~MainTemp()
{
    delete ui;
}

void MainTemp::createStatuses()
{
    GpuStatus *gpu = new GpuStatus(ui->centralWidget, this);
    gpu->show();
    gpu->move(10, 200);

    CpuStatus *cpu = new CpuStatus(ui->centralWidget, this);
    cpu->show();
    cpu->move(10, 400);

    MemoryStatus *mem = new MemoryStatus(ui->centralWidget, this);
    mem->show();
    mem->move(10, 600);
}

//Fetching and parsing device info
void MainTemp::getChipInfo()
{
    sensors_init(NULL);
    sensors_chip_name const * cn;

    int c = 0;

    summary = "Summary";
    cpuTemp.clear();
    //gpuTemp = "GPU";
    memoryTemp = "Memory\nRAM temp: ";

    while ((cn = sensors_get_detected_chips(0, &c)) != 0)
    {
        sensors_feature const *feat;
        int f = 0;

        while ((feat = sensors_get_features(cn, &f)) != 0)
        {
            //std::cout << "Label: " << sensors_get_label(cn,feat) << "\n\n\n";
            std::cout << f << ": " << feat->number << std::endl;

            sensors_subfeature const *subf;
            int s = 0;

            while ((subf = sensors_get_all_subfeatures(cn, feat, &s)) != 0)
            {
                std::cout << f << ":" << s << ":" << subf->name
                      << "/" << subf->number << " = ";
                double val;
                if (subf->flags & SENSORS_MODE_R)
                {
                    int rc = sensors_get_value(cn, subf->number, &val);
                    if (rc < 0)
                    {
                        std::cout << "err: " << rc;
                    }
                    else
                    {
                        if (c == SUMMARY)
                        {
                            summary += SUMMARY_STRINGS[subf->number];
                            if (subf->number == CPU_FAN_SLOT)
                            {
                                summary += QString::number(val) + " RPM";
                            }
                            else if (subf->number == RAM_SLOT)
                            {
                                summary += QString::number(val) + " °C";
                                memoryTemp += QString::number(val) + "°C";
                            }
                            else if (subf->number < SUMMARY_NUM)
                            {
                                summary += QString::number(val) + " °C";
                            }
                        }
                        else if (strcmp(cn->prefix,"coretemp") == 0)
                        {
                            QString temp;
                            temp += "\nCore " + QString::number(feat->number)
                                    + CPU_STRINGS[subf->number % CPU_NUM]
                                    + QString::number(val) + " °C";
                            cpuTemp.push_back(temp);
                        }
                        std::cout << val;
                    }
                }
                std::cout << std::endl;
            }
        }
    }

    ui->summary->setText(summary);

    sensors_cleanup();
}

void MainTemp::getDiskInfo()
{
    int sockfd, output_length = 0;
    ssize_t n = 1;
    struct sockaddr_in address;
    char* buffer, *pc;
    hddTemp = "Drives\n";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        //log error
        //return NULL;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(7634);

    buffer = NULL;

    if(::connect(sockfd, (struct sockaddr*)&address,
               (socklen_t) sizeof(address))== -1)
    {
        //error
    }
    else
    {
        buffer = (char*)malloc(4048);
        pc = buffer;

        while ((n = read(sockfd, pc, 4048 - output_length)) > 0)
        {
            output_length += n;
            pc = &pc[n];
        }
        buffer[output_length] = '\0';
    }
    ::close(sockfd);

    hddTemp += buffer;
}

//Slots
void MainTemp::updateGui()
{
    getChipInfo();
    getDiskInfo();
    notify();
}
