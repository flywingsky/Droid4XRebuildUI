#include "dxui.h"
#include "UIMsgMgr.h"
#include "mainpanel.h"
#include "toolbar.h"

DxUi::DxUi()
{

}

IMsgMgr *DxUi::GetMsgMgr()
{
    return CUIMsgMgr::GetMsgMgr();
}

void DxUi::CreateMainWnd()
{
    MainPanel* p = new MainPanel();
    p->show();

    ToolBar* t = new ToolBar(p);
    t->show();
}

