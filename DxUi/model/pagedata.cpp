#include "pagedata.h"

PageData::PageData(QObject *parent) : QObject(parent), page(NULL)
{

}

PageData::PageData(const PageData &other) :
    QObject(other.parent()),
    index(other.index),
    title(other.title),
    page(other.page)
{

}

