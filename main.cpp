#include "maintemp.h"
#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainTemp t;
    t.show();

    t.getSystemInfo();

    return a.exec();
}
