#include "mainwindow.h"
#include <QApplication>
#include <dispatcher.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dispatcher d;
    MainWindow w;
    QObject::connect(&w, SIGNAL(listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>)), &d, SLOT(newDep(QList<Periodical>, QList<EducLit>, QList<ImagLit>)));
    QObject::connect(&w, SIGNAL(getDeps(int)), &d, SLOT(getDeps(int)));
    QObject::connect(&d, SIGNAL(setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>)), &w, SIGNAL(setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>)));
    QObject::connect(&d, SIGNAL(error(QString)), &w, SLOT(error(QString)));
    QObject::connect(&w, SIGNAL(setLog(QString)), &d, SLOT(setLog(QString)));
    QObject::connect(&w, SIGNAL(getLog()), &d, SLOT(getLog()));
    QObject::connect(&d, SIGNAL(sendLog(QString)), &w, SIGNAL(sendLog(QString)));
    QObject::connect(&w, SIGNAL(getCount()), &d, SLOT(getCount()));
    QObject::connect(&d, SIGNAL(setCount(int)), &w, SIGNAL(setCount(int)));
    QObject::connect(&w, SIGNAL(listReady(QList<Periodical>, QList<EducLit>, QList<ImagLit>, int)), &d, SLOT(changeDep(QList<Periodical>, QList<EducLit>, QList<ImagLit>, int)));
    QObject::connect(&w, SIGNAL(clearLog()), &d, SLOT(clearLog()));
    QObject::connect(&w, SIGNAL(save()), &d, SLOT(save()));
    w.show();
    return a.exec();
}
