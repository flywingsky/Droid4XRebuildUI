#include "pagedata.h"

PageData::PageData(QObject *parent) :
    QObject(parent),
    page(NULL),
    item(NULL),
    itemWidget(NULL),
    mainPanel(NULL)
{

}

PageData::PageData(const PageData &other) :
    QObject(other.parent()),
    index(other.index),
    title(other.title),
    page(other.page),
    item(other.item),
    itemWidget(other.itemWidget),
    mainPanel(other.mainPanel)
{

}

