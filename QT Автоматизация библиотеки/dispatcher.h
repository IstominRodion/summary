#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <liblist.h>
#include <periodical.h>
#include <educlit.h>
#include <imaglit.h>
#include <QFile>
#include <QTextStream>

class dispatcher : public QObject
{
    Q_OBJECT
public:
    dispatcher();
    static LibList* getDisp();

private:
    LibList list;
    static LibList* pointer;
    QFile* logFile;
    QFile* saves;
    QTextStream log;
    QTextStream saver;
    void start();

signals:
    void setDeps(QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    void sendLog(QString);
    void error(QString);
    void setCount(int);

public slots:
    void newDep(QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    void getDeps(int);
    void setLog(QString);
    void getLog();
    void getCount();
    void changeDep(QList<Periodical>, QList<EducLit>, QList<ImagLit>, int);
    void clearLog();
    void save();
};

#endif // DISPATCHER_H
