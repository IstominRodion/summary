#include "periodical.h"

Periodical::Periodical()
{
}

Periodical::Periodical(QString title, QString author, QString period) : PrintedEdition(title, author)
{
    setPeriod(period);
}

void Periodical::setPeriod(QString str)
{
    period = str;
}

QString Periodical::getPeriod()
{
    return period;
}

QString Periodical::setFields()
{
    defaultList << "Вестник РАН, Вестник РАН, 1 раз в неделю";
    defaultList << "Дефектоскопия, Дефектоскопия, ежемесячно";
    defaultList << "Доклады АН, Доклады АН, ежемесячно";
    defaultList << "Журнал технической физики, Журнал технической физики, ежемесячно";
    defaultList << "Журнал экспериментальной и теоретической физики, Журнал экспериментальной и теоретической физики, 10 раз в год";
    defaultList << "Заводская лаборатория, Заводская лаборатория,ежемесячно";
    defaultList << "Известия вузов. Порошковая металлургия и функциональные покрытия, Известия вузов. Порошковая металлургия и функциональные покрытия, 10 раз в год";
    defaultList << "Известия вузов. Цветная металлургия, Известия вузов. Цветная металлургия, 10 раз в год";
    defaultList << "Известия РАН. Механика твердого тела, Известия РАН. Механика твердого тела, ежемесячно";
    defaultList << "Известия РАН. Серия физическая, Известия РАН. Серия физическая, 10 раз в год";
    defaultList << "7 Дней, 7 Дней, 1 раз в неделю";
    defaultList << "AD, AD, ежемесячно";
    defaultList << "Beauty,	Beauty, ежемесячно";
    defaultList << "Bolshoi sport, Bolshoi sport, ежемесячно";
    defaultList << "BRAVO Internatinal, BRAVO Internatinal, 1 раз в неделю";
    defaultList << "Building Business, Building Business, 10 раз в год";
    defaultList << "Building Commercial, Building Commercial, 10 раз в год";
    defaultList << "Building Life, Building Life, 10 раз в год";
    defaultList << "Burda / Бурда, Burda / Бурда, ежемесячно";
    defaultList << "BusinessWeek Россия, BusinessWeek Россия, 1 раз в неделю";
    int num = qrand() % 20;
    return defaultList[num];
}
