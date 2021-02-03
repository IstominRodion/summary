#include "view.h"
#include "ui_view.h"
#include <QShowEvent>

View::View(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);
    currentDep = 0;
    ui->label->setText("Отделение №1");
    emit getCount();
}

void View::showEvent(QShowEvent *event)
{
    emit getDeps(currentDep);
}

void View::setDeps(QList<Periodical> listP, QList<EducLit> listE, QList<ImagLit> listI)
{
    QList<Periodical>::iterator i;
    ui->plainTextEdit->setPlainText("Периодические издания:\n\n");
    for (i = listP.begin(); i < listP.end(); i++)
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + i->getTitle() + ", " + i->getAuthor() + ", " + i->getPeriod() + "\n");
    }
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nУчебная литература:\n\n");
    QList<EducLit>::iterator j;
    for (j = listE.begin(); j < listE.end(); j++)
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + j->getTitle() + ", " + j->getAuthor() + ", " + j->getSphere() + "\n");
    }
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + "\nХудожественная литература:\n\n");
    QList<ImagLit>::iterator k;
    for (k = listI.begin(); k < listI.end(); k++)
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + k->getTitle() + ", " + k->getAuthor() + ", " + k->getGenre() + "\n");
    }
}

View::~View()
{
    delete ui;
}

void View::on_pushButton_clicked()
{
    if (currentDep > 0)
        currentDep--;
    ui->label->setText("Отделение №" + QString::number(currentDep + 1));
    emit getDeps(currentDep);
}

void View::on_pushButton_2_clicked()
{
    emit getCount();
    if (currentDep < count - 1)
        currentDep++;
    ui->label->setText("Отделение №" + QString::number(currentDep + 1));
    emit getDeps(currentDep);
}

void View::clear()
{
    ui->plainTextEdit->toPlainText();
}

void View::setCount(int num)
{
    count = num;
}
