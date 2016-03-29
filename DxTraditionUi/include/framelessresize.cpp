#include "framelessresize.h"

#include <QEvent>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>

FramelessResize::FramelessResize(QObject *parent) : QObject(parent),
    _monitor(NULL),
    _target(NULL),
    _elastic(NULL),
    _pressDirection(NONE),
    _scale(0,0)

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

void FramelessResize::SetScale(QSize s,  QWidget* elastic)
{
    _scale = s;
    _elastic = elastic;
}

QSize FramelessResize::Scale() const
{
    return _scale;
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

    if(!offset.isNull())
    {
        offset = FixRatioTransform(offset,_scale, _monitor, _elastic);
        emit OffsetGeometry(offset);

        if(_target)
            _target->setGeometry(_target->geometry() + offset);
    }
}


QMargins FramelessResize::FixRatioTransform(const QMargins &g, const QSize& scale, const QWidget* parent, const QWidget* elastic)
{
    if(elastic == NULL || parent == NULL || g.isNull() || scale.isNull())
        return g;

    QSize fix = parent->size() - elastic->size();
    QSize intend = (elastic->geometry() + g).size();

    int sum = g.left()+g.top()+g.right()+g.bottom();
    QSize except = scale.scaled(intend, (sum > 0 ? Qt::KeepAspectRatioByExpanding : Qt::KeepAspectRatio)) + fix - parent->size();

    QMargins ret;

    qreal h = g.left() + g.right();
    qreal v = g.top() + g.bottom();

    if(h)
    {
        ret.setLeft(g.left() / h * except.width());
        ret.setRight(g.right() / h * except.width());
    }
    else
        ret.setRight(except.width());

    if(v)
    {
        ret.setTop(g.top() / v * except.height());
        ret.setBottom(g.bottom() / v * except.height());
    }
    else
        ret.setBottom(except.height());


    return ret;

}

QSize FramelessResize::ChangeRatioAdjust(const QSize &ratio, const QSize &parent, const QSize &byScale)
{
    QSize frame = parent - byScale;
    QSize ret = ratio.scaled(byScale,Qt::KeepAspectRatio);
    return ret + frame;
}

