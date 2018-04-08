#-------------------------------------------------
#
# Project created by QtCreator 2018-04-07T14:18:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = temp3000
TEMPLATE = app


SOURCES += main.cpp\
        maintemp.cpp \
    cpustatus.cpp \
    gpustatus.cpp \
    memorystatus.cpp

HEADERS  += maintemp.h \
    observer.h \
    cpustatus.h \
    gpustatus.h \
    memorystatus.h

FORMS    += maintemp.ui \
    cpustatus.ui \
    gpustatus.ui \
    memorystatus.ui

LIBS = /usr/include/sensors/sensors.h -lsensors
