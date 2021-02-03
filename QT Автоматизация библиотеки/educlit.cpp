#include "educlit.h"

EducLit::EducLit()
{
}

EducLit::EducLit(QString title, QString author, QString sphere) : PrintedEdition(title, author)
{
    setSphere(sphere);
}

void EducLit::setSphere(QString str)
{
    sphere = str;
}

QString EducLit::getSphere()
{
    return sphere;
}

QString EducLit::setFields()
{
    defaultList << "Гусев Е.И. Никифоров А.С. Коновалов А.Н., Нервные болезни; нейрохирургия., медицина";
    defaultList << "Триумфов А.В., Топическая диагностика заболеваний нервной системы, медицина";
    defaultList << "Скоромец А.А., Скоромец Т.А. Топическая диагностика заболеваний нервной системы, медицина";
    defaultList << "Бадалян Л.О., Детская неврология, медицина";
    defaultList << "Карлов В.А., Терапия нервных болезней, медицина";
    defaultList << "Карлов В.А., Неврология. Руководство для врачей, медицина";
    defaultList << "В.И.Гузева, Руководство по детской неврологии, медицина";
    defaultList << "Штульман Д.Р. Левин О.С., Cправочник практического врача по неврологии, медицина";
    defaultList << "Гусев Е.И. Коновалов А.Н. Бурд Г.С., Неврология и нейрохирургия, медицина";
    defaultList << "Бадалян Л.О., Детская неврология, медицина";
    int num = qrand() % 10;
    return defaultList[num];
}
