#include "dpitransform.h"

#include <QScreen>
#include <QApplication>
#include <QFont>
#include <QWidget>

#include <QDebug>

void DpiTransform::Transform()
{
    QScreen *screen = qApp->primaryScreen();
    qreal t = screen->logicalDotsPerInch() / 96.0;

    foreach (QWidget* p, qApp->allWidgets())
    {
        if(p->parent())
            p->move(p->pos() * t);
        p->setMinimumSize(p->minimumSize() * t);
        p->setMaximumSize(p->maximumSize() * t);
        p->resize(p->size() * t);
    }
}

DpiTransform::DpiTransform(QObject *parent) :
    QObject(parent)
{
}
