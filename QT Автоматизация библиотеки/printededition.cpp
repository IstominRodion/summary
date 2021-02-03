#include "printededition.h"

PrintedEdition::PrintedEdition()
{
}

PrintedEdition::PrintedEdition(QString title, QString author)
{
    setTitle(title);
    setAuthor(author);
}

void PrintedEdition::setTitle(QString str)
{
    title = str;
}

void PrintedEdition::setAuthor(QString str)
{
    author = str;
}

QString PrintedEdition::getTitle()
{
    return title;
}

QString PrintedEdition::getAuthor()
{
    return author;
}
