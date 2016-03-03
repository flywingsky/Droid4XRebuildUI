#include <QApplication>

#include "mainpanel.h"
#include "toolbar.h"

#include "UIMsgMgr.h"

#include <QDebug>

class TestMsg : public IMsgObsever
{
public:
    TestMsg()
    {
        IMsgMgr* mgr = CUIMsgMgr::GetMsgMgr();
        mgr->RegMsg(112,this,true);
        mgr->RegMsg(221,this,true);
    }

    unsigned long Notify(unsigned int auMsgID,void *apWParam,void *apLParam)
    {
        if(auMsgID == 112)
        {
            QString msg = *((QString*)apWParam);
            qDebug() << msg;
        }
        else if(auMsgID == 221)
        {
            QString msg = *((QString*)apLParam);
            qDebug() << msg;
        }

    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainPanel p;
    p.show();

    ToolBar t(&p);
    t.show();

    TestMsg tm;


    return a.exec();
}


