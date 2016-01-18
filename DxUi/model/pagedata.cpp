#include "pagedata.h"

PageData::PageData(QObject *parent) :
    QObject(parent),
    page(NULL)
{

}

PageData::PageData(const PageData &other) :
    QObject(other.parent()),
    title(other.title),
    page(other.page)
{

}

