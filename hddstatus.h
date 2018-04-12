#ifndef MEMORYSTATUS_H
#define MEMORYSTATUS_H

#include <QTextBrowser>
#include "maintemp.h"

namespace Ui {
class HddStatus;
}

class HddStatus : public QTextBrowser, public Observer
{
    Q_OBJECT

public:
    explicit HddStatus(QWidget *parent = 0, MainTemp *subject = 0);
    void update();

    ~HddStatus();

private:
    Ui::HddStatus *ui;
};

#endif // MEMORYSTATUS_H
