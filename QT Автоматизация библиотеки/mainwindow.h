#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <addition.h>
#include <periodical.h>
#include <educlit.h>
#include <imaglit.h>
#include <view.h>
#include <log.h>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void error(QString);

private slots:
    void on_action_triggered();
    void on_action_4_triggered();
    void on_action_3_triggered();

signals:
    void listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    void listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>, int);
    void getDeps(int);
    void setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    void renewView();
    void setLog(QString);
    void getLog();
    void sendLog(QString);
    void getCount();
    void setCount(int);
    void clearLog();
    void save();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent*);
};
#endif // MAINWINDOW_H
