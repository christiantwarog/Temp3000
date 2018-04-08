#ifndef GPUSTATUS_H
#define GPUSTATUS_H

#include <QTextBrowser>
#include "maintemp.h"

namespace Ui {
class GpuStatus;
}

class GpuStatus : public QTextBrowser, public Observer
{
    Q_OBJECT

public:
    explicit GpuStatus(QWidget *parent = 0, MainTemp *subject = 0);
    void update();

    ~GpuStatus();

private:
    Ui::GpuStatus *ui;
};

#endif // GPUSTATUS_H
