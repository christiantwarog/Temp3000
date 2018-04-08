#include "gpustatus.h"
#include "ui_gpustatus.h"

#include <iostream>

GpuStatus::GpuStatus(QWidget *parent, MainTemp *subject) :
    QTextBrowser(parent),
    Observer(subject),
    ui(new Ui::GpuStatus)
{
    ui->setupUi(this);
    subject->attach(this);
}

GpuStatus::~GpuStatus()
{
    delete ui;
}

void GpuStatus::update()
{
    setText(subject->getGpuTemp());
}
