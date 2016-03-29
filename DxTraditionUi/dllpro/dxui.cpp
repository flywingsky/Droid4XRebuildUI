#include "dxui.h"
#include "UIMsgMgr.h"
#include "mainpanel.h"
#include "toolbar.h"

#include "dxuiprivate.h"

DxUi::DxUi() :
    d_ptr(new DxUiPrivate(this))
{

}

IMsgMgr *DxUi::GetMsgMgr()
{
    return CUIMsgMgr::GetMsgMgr();
}

void DxUi::CreateMainWnd()
{
    Q_D(DxUi);
    d->_mainPanel = new MainPanel();
    d->_toolbar = new ToolBar(d->_mainPanel);
    d->_mainPanel->SetToolbar(d->_toolbar);
}


IUiProperty *DxUi::GetProperty() const
{
    return d_ptr;
}

DxUi::DxUi(DxUiPrivate *dd) :
    d_ptr(dd)
{

}

