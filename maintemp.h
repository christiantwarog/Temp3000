#ifndef MAINTEMP_H
#define MAINTEMP_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QString>
#include <iostream>
#include "observer.h"
#include <QTcpSocket>
#include <sensors/sensors.h>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

enum {
    NONE,
    SUMMARY,
    GPU,
    CPU
};
//Constants
static const int UI_REFRESH_RATE = 500;
static const char HDD_TEMP_ADDRESS[] = "127.0.0.1";
static const int HDD_TEMP_PORT = 7634;
static const int HDD_MESSAGE_SIZE = 4048;
static const int SUMMARY_NUM = 4;
static const int CPU_NUM = 4;
static const int MAX_CORE_NUM = 12;

static const int CPU_FAN_SLOT = 0;
static const int RAM_SLOT = 3;

static const char CPU_INFO[] = "cat /proc/cpuinfo | grep MHz";
static const char CPU_MHZ_STRING[] = "\nCPU Speed:";
static const char CPU_MHZ[] = " MHz";

static const QString SUMMARY_STRINGS[SUMMARY_NUM] =
{
    "\nCPU Fan: ",
    "\nCPU: ",
    "\nAmbient: ",
    "\nRAM: "
};

static const QString CORE_STRINGS[MAX_CORE_NUM+1] =
{
    "\nCPU ",
    "\nCore 1 ",
    "\nCore 2 ",
    "\nCore 3 ",
    "\nCore 4 ",
    "\nCore 5 ",
    "\nCore 6 ",
    "\nCore 7 ",
    "\nCore 8 ",
    "\nCore 9 ",
    "\nCore 10 ",
    "\nCore 11 ",
    "\nCore 12 "
};

static const QString CPU_STRINGS[CPU_NUM] =
{
    " temp: ",
    " max: ",
    " crit: ",
    " alarm: "
};

namespace Ui {
class MainTemp;
}

class MainTemp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainTemp(QWidget *parent = 0);
    void getChipInfo();

    void attach(Observer* obs)
    {
        observers.push_back(obs);
        qDebug() << "Attached";
    }

    void notify()
    {
        foreach(Observer* observer, observers)
        {
            observer->update();
        }
    }

    QVector<QString> getCpuTemp() { return cpuTemp; }
    QString getHddTemp() { return hddTemp; }

    ~MainTemp();

private:
    void createStatuses();
    void getDiskInfo();

    Ui::MainTemp *ui;
    QVector<Observer*> observers;

    QTimer* timer;

    //system info
    QString summary;
    QVector<QString> cpuTemp;
    QString hddTemp;

public slots:
    void updateGui();

};

#endif // MAINTEMP_H
