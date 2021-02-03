#include "dbproxy.h"

DBproxy* DBproxy::m_instance = 0;

DBproxy::DBproxy() : QObject(0)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath()+"/database.db");
    model = new QSqlTableModel(this);
}

DBproxy* DBproxy::getInstance()
{
    if (m_instance == nullptr) m_instance = new DBproxy();
    return m_instance;
}

void DBproxy::check()
{
    if (!db.open())
        emit dberror(db.lastError().text());
}

void DBproxy::newDep(int num)
{
    QString str = "create table if not exists `department'%1'`"
    "(id_ed INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
    "`title` VARCHAR(30), author VARCHAR(30), otherPar VARCHAR(30)";
    QString q = str.arg(QString::number(num));
    QSqlQuery query(db);
    if (query.exec(str))
        emit dbanswer("таблица `department" + QString::number(num) + "` создана или уже существует");
    else
        emit dberror(query.lastError().text());
}

void DBproxy::status()
{
    emit dbanswer(db.tables());
}

void DBproxy::save(LibList list)
{
    QString as, qIns, qUpd;
    qIns = "insert into `department'%1'` (title, author, otherPar) values ('%2', '%3', '%4')";
    qUpd = "update `department'%1'` set  id_ed = '%2', title = '%3', cost = '%4', prodDate = '%5', volume = '%6'";
    if (db.isOpen())
    {
        if (arg.getId()==0)
            as = qIns.arg(arg.getTitle()).arg(arg.getManufacturer()).arg(arg.getCost()).arg(arg.getProdDate().toString("yyyy-MM-dd")).arg(arg.getVolume());
        else
            as = qUpd.arg(arg.getId()).arg(arg.getTitle()).arg(arg.getManufacturer()).arg(arg.getCost()).arg(arg.getProdDate().toString("yyyy-MM-dd")).arg(arg.getVolume());
        QSqlQuery query(db);
        if (!query.exec(as))
            emit dberror(query.lastError().text());
        else
            emit dbanswer("данные о напитке сохранены");
    }
}

void DBproxy::find(drinks arg)
{
    QString str;
    bool howManyRows = false;
    QList<drinks> list;
    if (arg.getProdDate().isNull())
        str = "select id_drink, title, manufacturer, cost, prodDate, volume from drinks";
    else{
        str = "select id_drink, title, manufacturer, cost, prodDate, volume from drinks where prodDate between '";
        str+=arg.getProdDate().toString("yyyy-MM-dd")+"' and" + "'" + QDate::currentDate().toString("yyyy-MM-dd") + "'";
    }
    str+=" order by title asc;";
    if (db.isOpen()){
        QSqlQuery query(db);
        if (!query.exec(str))
            emit dbanswer(query.lastError().text());
        else
            while(query.next()){
                arg.setId(query.value(0).toInt());
                arg.setTitle(query.value(1).toString());
                arg.setManufacturer(query.value(2).toString());
                arg.setCost(query.value(3).toString());
                arg.setProdDate(query.value(4).toDate());
                arg.setVolume(query.value(5).toString());
                list.push_back(arg);
                howManyRows = true;
            }
    }
    emit dbanswer(list);
    if (howManyRows && list.count()!=0)
        emit dbanswer("Выборка выполнена");
    else
        emit dbanswer("Записи не найдены");
}

void DBproxy::renewTable(){
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    emit drinks_model(model);
}

void DBproxy::deleteFirst(){
    QString ask1 = "DELETE FROM `drinks`;", ask2 = "delete from sqlite_sequence where name='drinks';";
    if (db.isOpen()){
        QSqlQuery query(db);
        if (!query.exec(ask1))
            emit dbanswer(query.lastError().text());
        else
            emit dbanswer("Записи удалены");
        if (!query.exec(ask2))
            emit dbanswer(query.lastError().text());
        else
            emit dbanswer("Номер напитка поставлен на 1");
    }
}
