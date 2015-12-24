#include "framelessmove.h"

#include <QEvent>
#include <QMouseEvent>
#include <QWidget>

#include <QDebug>

void FramelessMove::SetFrameLess(bool less, QWidget *target)
{
    static const Qt::WindowFlags flags = Qt::FramelessWindowHint | Qt::WindowSystemMenuHint \
            | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint;

    if(target)
    {
        if (less)
            target->setWindowFlags(target->windowFlags() | flags);
        else
            target->setWindowFlags(target->windowFlags() & ~flags);
    }

}

FramelessMove::FramelessMove(QWidget *parent) :
    QObject(parent),
    _monitor(NULL),
    _target(NULL),
    lButtonPress(false)
{
}

void FramelessMove::SetMonitor(QWidget *monitor)
{
    _monitor = monitor;
    if(_monitor)
        _monitor->installEventFilter(this);
}

void FramelessMove::SetTarget(QWidget *target)
{
    _target = target;
}


void FramelessMove::SetFrameLess(bool less)
{
    SetFrameLess(less, _target);
}


bool FramelessMove::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == _monitor)
    {
        switch(ev->type())
        {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* event = (QMouseEvent*)ev;
            if(event->button() == Qt::LeftButton)
            {
                _offsetPos = event->globalPos();
                lButtonPress = true;
            }

            break;
        }
        case QEvent::MouseButtonRelease:
        {
            QMouseEvent* event = (QMouseEvent*)ev;
            if(event->button() == Qt::LeftButton && lButtonPress)
            {
                lButtonPress  = false;
            }

            break;
        }
        case QEvent::MouseMove:
        {
            if(lButtonPress)
            {
                QMouseEvent* event = (QMouseEvent*)ev;

                QPoint newPos = event->globalPos() - _offsetPos;
                emit MoveNewPos(newPos);

                if(_target)
                    _target->move(_target->pos() + newPos);

                _offsetPos = event->globalPos();


            }
            break;
        }
        case QEvent::Hide:
        {
            lButtonPress = false;
            break;
        }
        default:
            break;

        }
    }

    return false;
}
