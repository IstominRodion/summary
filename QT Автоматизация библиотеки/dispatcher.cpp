#include "dispatcher.h"
#include <QDateTime>
LibList* dispatcher::pointer = nullptr;

dispatcher::dispatcher()
{
    logFile = new QFile("events.log");
    if (logFile->exists())
        setLog("Начало работы программы");
    else
        if (logFile->open(QFile::WriteOnly))
            logFile->close();
    saves = new QFile("saves.log");
    if (!saves->exists())
        if (saves->open(QFile::WriteOnly))
            saves->close();
    saver.setCodec("ISO 8859-1");
    start();
    getDisp();
}

void dispatcher::start()
{
    if (saves->exists())
    {
        if (saves->open(QFile::ReadOnly))
        {
            saver.setDevice(saves);
            QString str = saver.readLine();
            int count;
            while (!saver.atEnd())
            {
                if (str.contains("Dep"))
                {
                    str = saver.readLine();
                    str = saver.readLine();
                    QList<Periodical> lP;
                    while (!str.contains("EducLit"))
                    {
                        QStringList temp = str.split(",");
                        Periodical per;
                        per.setTitle(temp[0]);
                        per.setAuthor(temp[1]);
                        per.setPeriod(temp[2]);
                        lP << per;
                        str = saver.readLine();
                    }
                    str = saver.readLine();
                    QList<EducLit> lE;
                    while (!str.contains("ImagLit"))
                    {
                        QStringList temp = str.split(",");
                        EducLit edu;
                        edu.setTitle(temp[0]);
                        edu.setAuthor(temp[1]);
                        edu.setSphere(temp[2]);
                        lE << edu;
                        str = saver.readLine();
                    }
                    str = saver.readLine();
                    QList<ImagLit> lI;
                    while (!str.contains("Dep") && str!="")
                    {
                        QStringList temp = str.split(",");
                        ImagLit img;
                        img.setTitle(temp[0]);
                        img.setAuthor(temp[1]);
                        img.setGenre(temp[2]);
                        lI << img;
                        str = saver.readLine();
                    }
                    getDisp()->add(lP, lE, lI);
                }
            }
            setLog("Сохранения считаны");
            saves->close();
        }
    }
}

LibList* dispatcher::getDisp()
{
    if (pointer == nullptr)
        pointer = new LibList();
    return pointer;
}

void dispatcher::newDep(QList<Periodical> list1, QList<EducLit> list2, QList<ImagLit> list3)
{
    getDisp()->add(list1, list2, list3);
}

void dispatcher::getDeps(int num)
{
    if (getDisp() != nullptr)
    {
        try {
            Library* temp = getDisp()->find(num);
            emit setDeps(temp->dataP, temp->dataE, temp->dataI);
        } catch (int errorNum) {
            if (errorNum == 2)
                emit error("Выход за пределы списка");
            else
                emit error("Нет элементов в списке");
        }

    }
}

void dispatcher::setLog(QString str)
{
    if (logFile->open(QFile::Append))
    {
        log.setDevice(logFile);
        log << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss")<< "    " << str << "\n";
        logFile->close();
    }
}

void dispatcher::getLog()
{
    setLog("Вызван просмотр журнала работы");
    QString str = "Журнал работы приложения:\n";
    if (logFile->open(QFile::ReadOnly))
    {
        log.setDevice(logFile);
        while (!log.atEnd())
            str += log.readLine()+"\n";
        logFile->close();
        emit sendLog(str);
    }
}

void dispatcher::getCount()
{
    emit setCount(getDisp()->length());
}

void dispatcher::changeDep(QList<Periodical> list1, QList<EducLit> list2, QList<ImagLit> list3, int num)
{
    getDisp()->change(list1, list2, list3, num);
}

void dispatcher::clearLog()
{
    if (logFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
        logFile->close();
}

void dispatcher::save()
{
    if (saves->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        saver.setDevice(saves);
        for (int i = 0; i < getDisp()->length(); i++)
        {
            saver << "Dep " << QString::number(i) << "\nPeriodical\n";
            QList<Periodical>::iterator per;
            for (per = getDisp()->find(i)->dataP.begin(); per < getDisp()->find(i)->dataP.end(); per++)
            {
                saver << per->getTitle() << "," << per->getAuthor() << "," << per->getPeriod() << "\n";
            }
            saver << "EducLit\n";
            QList<EducLit>::iterator edu;
            for (edu = getDisp()->find(i)->dataE.begin(); edu < getDisp()->find(i)->dataE.end(); edu++)
            {
                saver << edu->getTitle() << "," << edu->getAuthor() << "," << edu->getSphere() << "\n";
            }
            saver << "ImagLit\n";
            QList<ImagLit>::iterator img;
            for (img = getDisp()->find(i)->dataI.begin(); img < getDisp()->find(i)->dataI.end(); img++)
            {
                saver << img->getTitle() << "," << img->getAuthor() << "," << img->getGenre() << "\n";
            }
        }
        setLog("Отеделения сохранены");
        saves->close();
    }
}
