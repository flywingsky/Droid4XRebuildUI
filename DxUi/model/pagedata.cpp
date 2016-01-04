#include "pagedata.h"

PageData::PageData(QObject *parent) : QObject(parent)
{

}

PageData::PageData(const PageData &other) :
    index(other.index),
    title(other.title)
{

}

