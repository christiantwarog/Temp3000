#ifndef MAINTEMP_H
#define MAINTEMP_H

#include <QMainWindow>
#include <QVector>
#include <iostream>
#include "observer.h"

enum {
    NONE,
    SUMMARY,
    GPU,
    CPU
};
//Constants
static const int SUMMARY_NUM = 4;
static const int GPU_NUM = 4;
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

static const QString GPU_STRINGS[GPU_NUM] =
{
    "\nGPU temp: ",
    "\nGPU crit: "
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
    void getSystemInfo();

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
    QVector<QString> getHddTemp() { return hddTemp; }
    QString getMemoryTemp() { return memoryTemp; }

    ~MainTemp();

private:
    void createStatuses();
    Ui::MainTemp *ui;
    QVector<Observer*> observers;

    //GpuStatus *gpu;

    //system info
    QString summary;
    QVector<QString> cpuTemp;
    QString gpuTemp;
    QVector<QString> hddTemp;
    QString memoryTemp;
};

#endif // MAINTEMP_H
