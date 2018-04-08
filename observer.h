#ifndef OBSERVER_H
#define OBSERVER_H

#include <QMainWindow>

namespace Ui {
class Observer;
}

class MainTemp;

class Observer
{
public:
    MainTemp* subject;

    Observer(MainTemp* subject)
    {
        this->subject = subject;
    }

    virtual void update() = 0;
};

#endif // OBSERVER_H
