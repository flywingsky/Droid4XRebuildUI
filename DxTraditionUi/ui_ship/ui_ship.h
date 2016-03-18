#ifndef UI_SHIP_H
#define UI_SHIP_H

class DxUi;
class Ship;
class IUiProperty;
class IMsgMgr;

class ui_ship
{
public:
    ui_ship();

    void Run();

private:
    DxUi* _ui;
    Ship* _ship;
    IUiProperty* _uiProperty;
    IMsgMgr* _msgMgr;
};

#endif // UI_SHIP_H
