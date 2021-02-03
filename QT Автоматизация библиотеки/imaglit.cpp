#include "imaglit.h"

ImagLit::ImagLit()
{
}

ImagLit::ImagLit(QString title, QString author, QString genre) : PrintedEdition(title, author)
{
    setGenre(genre);
}

void ImagLit::setGenre(QString str)
{
    genre = str;
}

QString ImagLit::getGenre()
{
    return genre;
}

QString ImagLit::setFields()
{
    defaultList << "Война и мир, Лев Толстой, роман";
    defaultList << "1984, Джордж Оруэллб антиутопия";
    defaultList << "Улисс, Джеймс Джойс, роман";
    defaultList << "Лолита, Владимир Набоков, роман	";
    defaultList << "Шум и ярость, Уильям Фолкнер, роман";
    defaultList << "Человек-невидимка, Ральф Эллисон, роман";
    defaultList << "На маяк, Вирджиния Вулф, роман";
    defaultList << "Одиссея, Гомер, поэма";
    defaultList << "Гордость и предубеждение, Джейн Остен, роман";
    defaultList << "Поправка-22, Джозеф Хеллер, роман";
    int num = qrand() % 10;
    return defaultList[num];
}
