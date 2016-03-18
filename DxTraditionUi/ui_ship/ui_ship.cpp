#include "ui_ship.h"
#include "ship.h"
#include "dxui.h"
#include "IMsgObsever.h"
#include "iuiproperty.h"


#pragma comment(lib, "D4xShip.lib")
#pragma comment(lib, "dllpro.lib")

ui_ship::ui_ship() :
    _ui(NULL),
    _ship(NULL),
    _uiProperty(NULL),
    _msgMgr(NULL)
{

}

void ui_ship::Run()
{
    _ui = new DxUi();
    _ship = createShip();
    _uiProperty = _ui->GetProperty();
    _msgMgr = _ui->GetMsgMgr();

    _ui->CreateMainWnd();
    _ship->init(L"droid4x",(void*)_uiProperty->ScreenId(),_uiProperty->ScreenSize().width(), _uiProperty->ScreenSize().height());
    _ship->start(nullptr);

}

