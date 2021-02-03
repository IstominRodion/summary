#include "liblist.h"

// исключения:
// 0 - номер удаляемого элемента больше количства элементов в массиве
// 1 - удаление элемента по data, когда в списке нет элементов
// 2 - поиск элемента с большим индексом, чем есть в списке
// 3 - поиск в списке без элементов

LibList::LibList()
{
    firstItem = nullptr;
    lastItem = nullptr;
    count = 0;
}

//void LibList::createItem()
//{
//    Periodical p;
//    EducLit e;
//    ImagLit i;
//    QList<Periodical> item1;
//    QList<EducLit> item2;
//    QList<ImagLit> item3;
//    for (int j = 0; j < 3; j++)
//    {
//        p.setFields();
//        e.setFields();
//        i.setFields();
//        item1 << p;
//        item2 << e;
//        item3 << i;
//    }
//}

void LibList::add(QList<Periodical> item1, QList<EducLit> item2, QList<ImagLit> item3)
{
    if (firstItem == nullptr)
    {
        Library* temp = new Library(nullptr, nullptr, item1, item2, item3);
        firstItem = temp;
        lastItem = temp;
        count++;
        return;
    }
    if (firstItem == lastItem)
    {
        Library* temp = new Library(firstItem, nullptr, item1, item2, item3);
        firstItem->nextItem = temp;
        lastItem = temp;
        count++;
        return;
    }
    Library* temp = new Library(lastItem, nullptr, item1, item2, item3);
    lastItem->nextItem = temp;
    lastItem = temp;
    count++;
    return;
}

Library* LibList::find(int num)
{
    if (count == 0)
    {
        throw 3;
    }
    if (num >= count)
    {
        throw 2;
    }
    int curItem = 0;
    Library* temp = firstItem;
    for (int i = 0; i < num; i++)
    {
        temp = temp->nextItem;
        curItem++;
    }
    return temp;
}

void LibList::del(int num)
{
    if (num > count)
    {
        throw 0;
    }
    int curItem = 0;
    Library* temp = firstItem;
    for (int i = 0; i < num; i++)
    {
        temp = temp->nextItem;
        curItem++;
    }
    temp->prevItem->nextItem = temp->nextItem;
    temp->nextItem->prevItem = temp->prevItem;
}

void LibList::clear()
{
    while (firstItem!=nullptr)
    {
        Library* temp = lastItem;
        lastItem = lastItem->prevItem;
        delete[] temp;
    }
}

int LibList::length()
{
    return count;
}

void LibList::swap(Library* item1, Library* item2)
{
    Library* temp = item1;
    item1 = item2;
    item2 = temp;
}

LibList::~LibList()
{
    clear();
}

void LibList::change(QList<Periodical> item1, QList<EducLit> item2, QList<ImagLit> item3, int num)
{
    if (num > count)
    {
        throw 0;
    }
    int curItem = 0;
    Library* temp = firstItem;
    for (int i = 0; i < num; i++)
    {
        temp = temp->nextItem;
        curItem++;
    }
    temp->dataP = item1;
    temp->dataE = item2;
    temp->dataI = item3;
}
