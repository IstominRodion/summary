#ifndef DBPROXY_H
#define DBPROXY_H

#include <QObject>
#include <QtSql>
#include <liblist.h>

class DBproxy : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;
    static DBproxy* m_instance;
    QSqlTableModel* model;
    int currentDep;

public:
    void status();
    static DBproxy* getInstance();
    DBproxy();

signals:
    void dberror(QString);
    void dbanswer(QString);
    void dbanswer(QStringList);
    void dbanswer();
    void drinks_model(QSqlTableModel*);

public slots:
    void check();
    void newDep(int);
    void save(LibList);
    void find();
    void renewTable();
    void deleteFirst();
    void setCDep(int);
};

#endif // DBPROXY_H
