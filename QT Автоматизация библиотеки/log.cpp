#include "log.h"
#include "ui_log.h"

Log::Log(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);
}

void Log::showEvent(QShowEvent *event)
{
    emit getLog();
}

void Log::sendLog(QString str)
{
    ui->textEdit->setText(str);
}

Log::~Log()
{
    delete ui;
}

void Log::on_pushButton_clicked()
{
    emit clearLog();
    emit getLog();
}
