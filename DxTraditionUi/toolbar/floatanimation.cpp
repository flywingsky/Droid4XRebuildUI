#include "floatanimation.h"

#include <QEvent>
#include <QHoverEvent>
#include <QWidget>
#include <QState>
#include <QStateMachine>
#include <QPropertyAnimation>
#include <QSignalTransition>

#include <QDebug>


FloatAnimation::FloatAnimation(QObject *parent) :
    QObject(parent),
    _monitor(NULL),
    _target(NULL),
    _show(new QState()),
    _hide(new QState()),
    _hideAnim(new QPropertyAnimation),
    _showAnim(new QPropertyAnimation),
    _machine(new QStateMachine(this))


{
    _hide->addTransition(this, SIGNAL(Show()), _show)->addAnimation(_showAnim);
    _show->addTransition(this, SIGNAL(Hide()), _hide)->addAnimation(_hideAnim);
    _machine->addState(_show);
    _machine->addState(_hide);

    _showAnim->setDuration(1000);
    _hideAnim->setDuration(1000);


}

void FloatAnimation::SetMonitor(QWidget *p)
{
    if(_monitor != p)
    {
        _monitor = p;
        p->installEventFilter(this);
    }
}

void FloatAnimation::SetTarget(QWidget *t)
{
    if(t != _target)
    {
        _target = t;

        _showAnim->setPropertyName("geometry");
        _showAnim->setTargetObject(_target);
        _hideAnim->setPropertyName("geometry");
        _hideAnim->setTargetObject(_target);


    }
}

void FloatAnimation::Start()
{
    Q_ASSERT(_monitor);
    Q_ASSERT(_target);

    InitValue();
    _machine->setInitialState(_show);
    _machine->start();
    emit Hide();


}

void FloatAnimation::Stop()
{
    _machine->stop();
}


bool FloatAnimation::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == _monitor)
    {
        switch(ev->type())
        {
        case QEvent::HoverMove:
        {
            if(_machine->isRunning())
            {
                QHoverEvent* e = (QHoverEvent*)ev;
                if(_showTrigger.contains(e->pos()) || _target->geometry().contains(e->pos()))
                    emit Show();
                if(_hideTrigget.contains(e->pos()))
                    emit Hide();
            }
            break;
        }
        default:
            break;
        }
    }
    return QObject::eventFilter(obj,ev);
}

void FloatAnimation::InitValue()
{
    QRect show;
    QRect hide;
    if(_target->maximumHeight() == QWIDGETSIZE_MAX) // portrait
    {
        show = QRect(QPoint(0,0),QSize(_target->maximumWidth(),_monitor->height()));
        hide = QRect(QPoint(0,0),QSize(0,_monitor->height()));

        _showTrigger = QRect(0,0,4,show.height());
        _hideTrigget = QRect(show.width(),0,_monitor->width() - show.width(), _monitor->height());
    }
    else // landscape
    {
        show = QRect(0,_monitor->height() - _target->maximumHeight(),_monitor->width(),_target->maximumHeight());
        hide = QRect(0,_monitor->height(),_monitor->width(),0);

        _showTrigger = QRect(0,_monitor->height() - 4,_monitor->width(),4);
        _hideTrigget = QRect(0,0,_monitor->width(),_monitor->height() - show.height());
    }

    _show->assignProperty(_target,"geometry",show);
    _hide->assignProperty(_target,"geometry",hide);

    _showAnim->setKeyValueAt(0,hide);
    _showAnim->setKeyValueAt(0.8,hide);
    _showAnim->setKeyValueAt(1,show);

    _hideAnim->setKeyValueAt(0,show);
    _hideAnim->setKeyValueAt(0.8,show);
    _hideAnim->setKeyValueAt(1,hide);





}

