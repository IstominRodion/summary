#ifndef EDUCLIT_H
#define EDUCLIT_H

#include <printededition.h>
#include <qstring.h>
#include <qstringlist.h>

class EducLit : public PrintedEdition
{
public:
    EducLit();
    EducLit(QString, QString, QString);
    void setSphere(QString);
    QString getSphere();
    QString setFields();

private:
    QString sphere;
    QStringList defaultList;
};

#endif // EDUCLIT_H
