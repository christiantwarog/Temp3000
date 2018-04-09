#include "maintemp.h"
#include "ui_maintemp.h"
#include "cpustatus.h"
#include "hddstatus.h"
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
    timer->start(UI_REFRESH_RATE);
}

MainTemp::~MainTemp()
{
    delete ui;
}

/*
 * createStatuses creates instances of CpuStatus and HddStatus and
 * adds them to its ui form
 */
void MainTemp::createStatuses()
{
    CpuStatus *cpu = new CpuStatus(ui->backgroundWidget, this);
    cpu->show();
    cpu->move(10, 200);

    HddStatus *mem = new HddStatus(ui->backgroundWidget, this);
    mem->show();
    mem->move(10, 400);
}

/*
 * getChipInfo retrieves CPU, RAM and Ambient temerature values from
 * hwmon using the libsensors api
 */
void MainTemp::getChipInfo()
{
    sensors_init(NULL);
    sensors_chip_name const * cn;
    int count = 0;

    summary = "\n\n";
    cpuTemp.clear();

    qDebug() << "Fetching CPU and RAM data\n";
    while ((cn = sensors_get_detected_chips(0, &count)) != 0)
    {
        qDebug() << cn->prefix;
        sensors_feature const *sensorFeature;
        int f = 0;

        while ((sensorFeature = sensors_get_features(cn, &f)) != 0)
        {
            qDebug() << sensorFeature->name;
            sensors_subfeature const *subf;
            int s = 0;

            while ((subf = sensors_get_all_subfeatures(cn, sensorFeature, &s)) != 0)
            {
                double val;
                if (subf->flags & SENSORS_MODE_R)
                {
                    int rc = sensors_get_value(cn, subf->number, &val);
                    if (rc < 0)
                        log(QString::number(rc) + ": Error, sensor did not report value");
                    else
                    {
                        if (count == SUMMARY && subf->number < SUMMARY_NUM)
                        {
                            summary += SUMMARY_STRINGS[subf->number];
                            if (subf->number == CPU_FAN_SLOT)
                                summary += QString::number(val) + " RPM";
                            else
                                summary += QString::number(val) + "°C";
                        }
                        else if (strcmp(cn->prefix,"coretemp") == 0)
                        {
                            QString temp;
                            if (subf->number % CPU_NUM == 0)
                                temp += "\nCore " + QString::number(sensorFeature->number);

                            temp += CPU_STRINGS[subf->number % CPU_NUM]
                                    + QString::number(val) + "°C";
                            cpuTemp.push_back(temp);
                        }
                        qDebug() << s << ":" << subf->name << " = " << val;
                    }
                }
            }
            qDebug() << "";
        }
        qDebug() << "";
    }

    qDebug() << "Done fetching CPU and RAM data";
    ui->summary->setText(summary);

    sensors_cleanup();
}

/*
 * getDiskInfo retrieves the temperature information for all drives
 * that are supported by Hddtemp over a TCP connection
 */
void MainTemp::getDiskInfo()
{
    int sock, output_length = 0;
    ssize_t n = 1;
    struct sockaddr_in address;
    char* buffer = NULL, *pc;
    hddTemp = "\n\n\n";

    qDebug() << "Fetching HDD data\n";
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1)
        log("Socket could not be created.");
    else
    {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(HDD_TEMP_ADDRESS);
        address.sin_port = htons(HDD_TEMP_PORT);

        if(::connect(sock, (struct sockaddr*)&address, (socklen_t) sizeof(address))== -1)
            log("Conection to Hddtemp daemon failed.");
        else
        {
            buffer = (char*)malloc(HDD_MESSAGE_SIZE);
            pc = buffer;
            while ((n = read(sock, pc, HDD_MESSAGE_SIZE - output_length)) > 0)
            {
                output_length += n;
                pc = &pc[n];
            }
            buffer[output_length] = '\0';
        }
        ::close(sock);
        hddTemp += buffer;
        qDebug() << buffer;
        qDebug() << "\nDone fetching HDD data";
    }
}

/*
 * updateGui retrieves chip and disk info
 * then notifies the status classes of the updated information
 */
void MainTemp::updateGui()
{
    getChipInfo();
    getDiskInfo();
    notify();
}

/*
 * log adds a message to the log file specified in settings file
 */
void MainTemp::log(QString message)
{
    //TODO: implement file locking to a log file
    qDebug() << message;
}

