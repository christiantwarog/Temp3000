#include "memorystatus.h"
#include "ui_memorystatus.h"

MemoryStatus::MemoryStatus(QWidget *parent, MainTemp *subject) :
    QTextBrowser(parent),
    Observer(subject),
    ui(new Ui::MemoryStatus)
{
    ui->setupUi(this);
    subject->attach(this);
}

MemoryStatus::~MemoryStatus()
{
    delete ui;
}

void MemoryStatus::update()
{
    setText(subject->getHddTemp());
}
