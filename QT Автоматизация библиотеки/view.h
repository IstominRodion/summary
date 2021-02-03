#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <periodical.h>
#include <educlit.h>
#include <imaglit.h>


namespace Ui {
class View;
}

class View : public QWidget
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

signals:
    void getDeps(int);
    void getCount();

public slots:
    void setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    void clear();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void setCount(int);

private:
    Ui::View *ui;
    int currentDep;
    int count;
    void showEvent(QShowEvent *event);
};

#endif // VIEW_H
