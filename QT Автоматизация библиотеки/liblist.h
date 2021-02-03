#ifndef LIBLIST_H
#define LIBLIST_H

#include <QObject>
#include <library.h>
#include <periodical.h>
#include <educlit.h>
#include <imaglit.h>

class LibList : public QObject
{
public:
    LibList();
    void add(QList<Periodical>, QList<EducLit>, QList<ImagLit>);
    Library* find(int);
    void del(int);
    void clear();
    int length();
    void swap(Library*, Library*);
    void change(QList<Periodical>, QList<EducLit>, QList<ImagLit>, int);
    ~LibList();

private:
    Library* firstItem;
    Library* lastItem;
    int count;
};

#endif // LIBLIST_H
