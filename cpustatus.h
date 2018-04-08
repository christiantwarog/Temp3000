#ifndef CPUSTATUS_H
#define CPUSTATUS_H

#include <QTextBrowser>
#include "maintemp.h"

namespace Ui {
class CpuStatus;
}

class CpuStatus : public QTextBrowser, public Observer
{
    Q_OBJECT

public:
    CpuStatus(QWidget *parent = 0, MainTemp *subject = 0);
    void update();

    ~CpuStatus();

private:
    Ui::CpuStatus *ui;
};

#endif // CPUSTATUS_H
