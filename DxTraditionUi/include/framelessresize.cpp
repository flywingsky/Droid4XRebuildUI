#include "framelessresize.h"

#include <QEvent>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>

FramelessResize::FramelessResize(QObject *parent) : QObject(parent),
    _monitor(NULL),
    _target(NULL),
    _pressDirection(NONE)
{

}

void FramelessResize::SetMonitor(QWidget *p)
{
    Q_ASSERT(p);
    _monitor = p;
    _monitor->setAttribute(Qt::WA_Hover);
    _monitor->installEventFilter(this);
}

void FramelessResize::SetTarget(QWidget *p)
{
    Q_ASSERT(p);
    _target = p;
}

void FramelessResize::SetBorderWidth(int w)
{
    _borderWidth = w;
}

int FramelessResize::BorderWidth()
{
    return _borderWidth;
}

bool FramelessResize::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == _monitor)
    {
        switch(ev->type())
        {
        case QEvent::HoverMove:
        {
            QHoverEvent* e = (QHoverEvent*)ev;
            SetCursor(GetDirection(e->pos()));
            DragResize(ev);
            break;
        }
        case QEvent::MouseButtonPress:
        {
            QMouseEvent* e = (QMouseEvent*)ev;
            _pressDirection = GetDirection(e->pos());
            break;
        }
        case QEvent::MouseButtonRelease:
        {
            _pressDirection = NONE;
            break;
        }
        default:
            break;
        }
    }
    return QObject::eventFilter(obj, ev);
}


int FramelessResize::GetDirection(const QPoint pt) const
{
    Q_ASSERT(_monitor);

    int h = NONE;
    int v = NONE;

    if(pt.x() < _borderWidth)
         h = LEFT;
    else if(pt.x() > _monitor->width() - _borderWidth)
        h = RIGHT;

    if(pt.y() < _borderWidth)
        v = TOP;
    else if(pt.y() > _monitor->height() - _borderWidth)
        v = BOTTOM;

    return v | h;

}


void FramelessResize::SetCursor(int direction)
{
    Q_ASSERT(_monitor);

    static QCursor primary = _monitor->cursor();

    if(direction == LEFTTOP || direction == RIGHTBOTTOM)
        _monitor->setCursor(QCursor(Qt::SizeFDiagCursor));
    else if(direction == RIGHTTOP || direction == LEFTBOTTOM)
        _monitor->setCursor(QCursor(Qt::SizeBDiagCursor));
    else if(direction == LEFT || direction == RIGHT)
        _monitor->setCursor(QCursor(Qt::SizeHorCursor));
    else if(direction == TOP || direction == BOTTOM)
        _monitor->setCursor(QCursor(Qt::SizeVerCursor));
    else
        _monitor->setCursor(primary);
}

void FramelessResize::DragResize(QEvent *ev)
{
    QHoverEvent* e = (QHoverEvent*)ev;
    QMargins offset;
    if(_pressDirection & LEFT)
        offset.setLeft((e->oldPos() - e->pos()).x());
    if(_pressDirection & RIGHT)
        offset.setRight((e->pos() - e->oldPos() ).x());
    if(_pressDirection & TOP)
        offset.setTop((e->oldPos() - e->pos()).y());
    if(_pressDirection & BOTTOM)
        offset.setBottom((e->pos() - e->oldPos() ).y());

    emit OffsetGeometry(offset);

    if(_target)
        _target->setGeometry(_target->geometry() + offset);
}
