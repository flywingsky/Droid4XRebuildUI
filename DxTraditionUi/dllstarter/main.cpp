#include <QApplication>


#include "dxui.h"
#include "IMsgObsever.h"
#include "iuiproperty.h"
#include "msgdef.h"

#pragma comment(lib, "dllpro.lib")


#include <QDebug>
#include <QKeyEvent>
#include <QPoint>

class TestMsg : public IMsgObsever
{
public:

    virtual unsigned long Notify(unsigned int id,void *wparam,void *lparam)
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
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DxUi* ui = new DxUi();
    ui->CreateMainWnd();

    TestMsg* t = new TestMsg;

    IMsgMgr* msg = ui->GetMsgMgr();
    msg->RegMsg(InOut::MousePress, t, true);
    msg->RegMsg(InOut::MouseRelease, t, true);
    msg->RegMsg(InOut::MouseMove, t, true);
    msg->RegMsg(InOut::StringInput, t, true);
    msg->RegMsg(InOut::KeyDown, t, true);

    IUiProperty* property = ui->GetProperty();
    qDebug()<< property->PanelSize();
    qDebug() << property->PanelPos();


    return a.exec();
}
