#ifndef PERIODICAL_H
#define PERIODICAL_H

#include <printededition.h>
#include <qstring.h>
#include <qstringlist.h>

class Periodical : public PrintedEdition
{
public:
    Periodical();
    Periodical(QString, QString, QString);
    void setPeriod(QString);
    QString getPeriod();
    QString setFields();

private:
    QString period;
    QStringList defaultList;
};

#endif // PERIODICAL_H
