#ifndef MAINTEMP_H
#define MAINTEMP_H

#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <iostream>
#include "observer.h"
#include <QTcpSocket>

enum {
    NONE,
    SUMMARY,
    GPU,
    CPU
};
//Constants
static const int SUMMARY_NUM = 4;
//static const int GPU_NUM = 4;
static const int CPU_NUM = 4;

static const int CPU_FAN_SLOT = 0;
static const int RAM_SLOT = 3;

static const QString SUMMARY_STRINGS[SUMMARY_NUM] =
{
    "\nCPU Fan: ",
    "\nCPU: ",
    "\nAmbient: ",
    "\nRAM: "
};

/*static const QString GPU_STRINGS[GPU_NUM] =
{
    "\nGPU temp: ",
    "\nGPU crit: "
};*/

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
        std::cout << "Attached\n";
    }

    void notify()
    {
        foreach(Observer* observer, observers)
        {
            observer->update();
        }
    }

    QVector<QString> getCpuTemp() { return cpuTemp; }
    QString getGpuTemp() { return gpuTemp; }
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
    QString gpuTemp;
    QString hddTemp;
    QString memoryTemp;

    QTcpSocket* _pSocket;

public slots:
    void updateGui();

};

#endif // MAINTEMP_H
