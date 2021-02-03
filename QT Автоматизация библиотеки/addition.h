#ifndef ADDITION_H
#define ADDITION_H

#include <QWidget>
#include <printededition.h>
#include <periodical.h>
#include <educlit.h>
#include <imaglit.h>
#include <QShowEvent>

namespace Ui {
class Addition;
}

class Addition : public QWidget
{
    Q_OBJECT

public:
    explicit Addition(QWidget *parent = nullptr);
    ~Addition();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    void setCount(int);

signals:
    void listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    void listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>, int);
    void setLog(QString);
    void getDeps(int);
    void error(QString);
    void getCount();

private:
    Ui::Addition *ui;
    static int count;
    void setComboItems();
    QList<Periodical> listP;
    QList<EducLit> listE;
    QList<ImagLit> listI;
    void showEvent(QShowEvent *event);
};

#endif // ADDITION_H
