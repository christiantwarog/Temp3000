#ifndef MEMORYSTATUS_H
#define MEMORYSTATUS_H

#include <QTextBrowser>
#include "maintemp.h"

namespace Ui {
class MemoryStatus;
}

class MemoryStatus : public QTextBrowser, public Observer
{
    Q_OBJECT

public:
    explicit MemoryStatus(QWidget *parent = 0, MainTemp *subject = 0);
    void update();

    ~MemoryStatus();

private:
    Ui::MemoryStatus *ui;
};

#endif // MEMORYSTATUS_H
