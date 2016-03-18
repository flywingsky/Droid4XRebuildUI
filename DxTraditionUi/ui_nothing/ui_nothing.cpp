#include "ui_nothing.h"
#include "dxui.h"
#include "iuiproperty.h"
#include "msgtest.h"

#include <QDebug>
#include <QSize>
#include <QPoint>

#include "IMsgObsever.h"



ui_nothing::ui_nothing():
    _ui(NULL),
    _uiProperty(NULL),
    _msgMgr(NULL)
{

}

void ui_nothing::Run()
{
    _ui = new DxUi();
    _test = new MsgTest();
    _msgMgr = _ui->GetMsgMgr();
    _uiProperty = _ui->GetProperty();


    _ui->CreateMainWnd();
    _test->RegisterMsg(_msgMgr);



    qDebug()<< _uiProperty->PanelSize();
    qDebug() << _uiProperty->PanelPos();
}

