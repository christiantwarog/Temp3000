#include "hddstatus.h"
#include "ui_hddstatus.h"

HddStatus::HddStatus(QWidget *parent, MainTemp *subject) :
    QTextBrowser(parent),
    Observer(subject),
    ui(new Ui::HddStatus)
{
    ui->setupUi(this);
    subject->attach(this);
}

HddStatus::~HddStatus()
{
    delete ui;
}

void HddStatus::update()
{
    setText(subject->getHddTemp());
}
