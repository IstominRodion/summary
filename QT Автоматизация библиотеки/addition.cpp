#include "addition.h"
#include "ui_addition.h"

int Addition::count = 1;

Addition::Addition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Addition)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Новое");
}

void Addition::showEvent(QShowEvent *event)
{
    emit getCount();
    ui->label->setText("Отделение №" + QString::number(count));
    setComboItems();
}

Addition::~Addition()
{
    delete ui;
}

void Addition::on_pushButton_clicked()
{
    QString str = ui->plainTextEdit->toPlainText();
    QStringList list = str.split("\n");
    QList<Periodical> listPer;
    QStringList::iterator i;
    for (i = list.begin(); i < list.end(); i++)
    {
        if (!i->isEmpty())
        {
            QStringList temp;
            for (int n = 0; n < 3; n++)
            {
                temp << "";
            }
            int num = 0;
            foreach (QString str, i->split(","))
            {
                temp[num++] = str;

            }
            Periodical book(temp[0],temp[1],temp[2]);
            listPer << book;
        }
    }

    list.clear();
    str = ui->plainTextEdit_2->toPlainText();
    list = str.split("\n");
    QList<EducLit> listEdu;
    for (i = list.begin(); i < list.end(); i++)
    {
        if (!i->isEmpty())
        {
            QStringList temp;
            for (int n = 0; n < 3; n++)
            {
                temp << "";
            }
            int num = 0;
            foreach (QString str, i->split(","))
            {
                temp[num++] = str;

            }
            EducLit book(temp[0],temp[1],temp[2]);
            listEdu << book;
        }
    }

    list.clear();
    str = ui->plainTextEdit_3->toPlainText();
    list = str.split("\n");
    QList<ImagLit> listImg;
    for (i = list.begin(); i < list.end(); i++)
    {
        if (!i->isEmpty())
        {
            QStringList temp;
            for (int n = 0; n < 3; n++)
            {
                temp << "";
            }
            int num = 0;
            foreach (QString str, i->split(","))
            {
                temp[num++] = str;

            }
            ImagLit book(temp[0],temp[1],temp[2]);
            listImg << book;
        }
    }
    if (ui->comboBox->currentIndex()==0)
    {
        emit listReady(listPer, listEdu, listImg);
        emit setLog("Добавлено отделение № " + QString::number(count));
        ui->comboBox->addItem("Отд. №" + QString::number(count));
        count++;
        ui->label->setText("Отделение №" + QString::number(count));
        ui->plainTextEdit->clear();
        ui->plainTextEdit_2->clear();
        ui->plainTextEdit_3->clear();
    }
    else
    {
        emit listReady(listPer, listEdu, listImg, ui->comboBox->currentIndex() - 1);
        emit setLog("Внесены изменения в отделение №" + QString::number(ui->comboBox->currentIndex()));
    }
}

void Addition::on_pushButton_2_clicked()
{
    Periodical p;
    EducLit e;
    ImagLit i;
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + p.setFields() + "\n");
    ui->plainTextEdit_2->setPlainText(ui->plainTextEdit_2->toPlainText() + e.setFields() + "\n");
    ui->plainTextEdit_3->setPlainText(ui->plainTextEdit_3->toPlainText() + i.setFields() + "\n");
}

void Addition::setComboItems()
{
    for (int i = 1; i < count; i++)
    {
        ui->comboBox->addItem("Отд. №" + QString::number(i));
    }
}

void Addition::on_comboBox_currentIndexChanged(int index)
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_3->clear();
    if (index!=0)
    {
        emit getDeps(index - 1);
        ui->label->setText("Отделение №" + QString::number(index));
        QList<Periodical>::iterator i;
        for (i = listP.begin(); i < listP.end(); i++)
        {
            ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + i->getTitle() + "," + i->getAuthor() + "," + i->getPeriod() + "\n");
        }
        QList<EducLit>::iterator j;
        for (j = listE.begin(); j < listE.end(); j++)
        {
            ui->plainTextEdit_2->setPlainText(ui->plainTextEdit_2->toPlainText() + j->getTitle() + "," + j->getAuthor() + "," + j->getSphere() + "\n");
        }
        QList<ImagLit>::iterator k;
        for (k = listI.begin(); k < listI.end(); k++)
        {
            ui->plainTextEdit_3->setPlainText(ui->plainTextEdit_3->toPlainText() + k->getTitle() + "," + k->getAuthor() + "," + k->getGenre() + "\n");
        }
    }
    else
        ui->label->setText("Отделение №" + QString::number(count));
}

void Addition::setDeps(QList<Periodical> lP, QList<EducLit> lE, QList<ImagLit> lI)
{
    listP = lP;
    listE = lE;
    listI = lI;
}

void Addition::setCount(int num)
{
    count = num + 1;
}
