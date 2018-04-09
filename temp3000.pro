#-------------------------------------------------
#
# Project created by QtCreator 2018-04-07T14:18:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = temp3000
TEMPLATE = app


SOURCES += main.cpp\
        maintemp.cpp \
    cpustatus.cpp \
    hddstatus.cpp

HEADERS  += maintemp.h \
    observer.h \
    cpustatus.h \
    hddstatus.h

FORMS    += maintemp.ui \
    cpustatus.ui \
    hddstatus.ui

LIBS = /usr/include/sensors/sensors.h -lsensors
