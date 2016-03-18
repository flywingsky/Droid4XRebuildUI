#include "msgtest.h"

#include <QDebug>
#include "IMsgObsever.h"
#include "msgdef.h"

MsgTest::MsgTest()
{

}

void MsgTest::RegisterMsg(IMsgMgr *obj)
{
    obj->RegMsg(InOut::MousePress, this, true);
    obj->RegMsg(InOut::MouseRelease, this, true);
    obj->RegMsg(InOut::MouseMove, this, true);
    obj->RegMsg(InOut::StringInput, this, true);
    obj->RegMsg(InOut::KeyDown, this, true);
}

unsigned long MsgTest::Notify(unsigned int id, void *wparam, void *lparam)
{
    switch(id)
    {
    case InOut::MousePress:
    {
        QPoint* pt = (QPoint*)wparam;
        qDebug() << "MousePress" << pt;
        break;
    }
    case InOut::MouseRelease:
    {
        qDebug() << "MouseRelease";
        break;
    }
    case InOut::MouseMove:
    {
        QPoint* pt = (QPoint*)wparam;
        qDebug() << "MouseMove" << pt;
        break;
    }
    case InOut::KeyDown:
    {
        long* vk = (long*)wparam;
        qDebug() << "KeyDown" << *vk;

        break;
    }
    case InOut::StringInput:
    {
        QString* s = (QString*)wparam;
        qDebug() << "StringInput" << *s;
        break;
    }
    default:
        break;
    }
    return 0;
}

