#ifndef LIBRARY_H
#define LIBRARY_H

#include <printededition.h>
#include <qlist.h>
#include <periodical.h>
#include <educlit.h>
#include <imaglit.h>

class Library
{
public:
    Library(Library*, Library*, QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    Library* prevItem;
    Library* nextItem;
    QList<Periodical> dataP;
    QList<EducLit> dataE;
    QList<ImagLit> dataI;
    void setFields();
};

#endif // LIBRARY_H
