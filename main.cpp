#include "maintemp.h"
#include <QApplication>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainTemp t;
    t.setStyleSheet("QMainWindow {background: 'grey';}");
    t.show();

    //syscall("sudo hddtemp /dev/sd[abcdefghi]");

    return a.exec();
}
