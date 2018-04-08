#include "cpustatus.h"
#include "ui_cpustatus.h"

CpuStatus::CpuStatus(QWidget *parent, MainTemp *subject) :
    QTextBrowser(parent),
    Observer(subject),
    ui(new Ui::CpuStatus)
{
    ui->setupUi(this);
    subject->attach(this);
}

CpuStatus::~CpuStatus()
{
    delete ui;
}

void CpuStatus::update()
{
    QString format = "CPU";
    QVector<QString> data = subject->getCpuTemp();
    for (int i = 0; i < data.size(); i++)
    {
        format += data[i];
    }
    setText(format);
}
