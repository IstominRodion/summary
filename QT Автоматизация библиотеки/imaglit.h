#ifndef IMAGLIT_H
#define IMAGLIT_H

#include <printededition.h>
#include <qstring.h>
#include <qstringlist.h>

class ImagLit : public PrintedEdition
{
public:
    ImagLit();
    ImagLit(QString, QString, QString);
    void setGenre(QString);
    QString getGenre();
    QString setFields();

private:
    QString genre;
    QStringList defaultList;
};

#endif // IMAGLIT_H
