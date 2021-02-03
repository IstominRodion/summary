#ifndef PRINTEDEDITION_H
#define PRINTEDEDITION_H

#include <qstring.h>

class PrintedEdition
{
public:
    PrintedEdition();
    PrintedEdition(QString, QString);
    void setTitle(QString);
    void setAuthor(QString);
    QString getTitle();
    QString getAuthor();

private:
    QString title;
    QString author;
};

#endif // PRINTEDEDITION_H
