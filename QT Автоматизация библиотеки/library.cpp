#include "library.h"

Library::Library(Library* prev, Library* next, QList<Periodical> dP, QList<EducLit> dE, QList<ImagLit> dI)
    : prevItem(prev), nextItem(next), dataP(dP), dataE(dE), dataI(dI)
{
}

void Library::setFields()
{
    QList<Periodical> listP;
    QList<EducLit> listE;
    QList<ImagLit> listI;
}
