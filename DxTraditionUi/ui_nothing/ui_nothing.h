#ifndef UI_NOTHING_H
#define UI_NOTHING_H


class DxUi;
class IUiProperty;
class IMsgMgr;
class MsgTest;

class ui_nothing
{
public:
    ui_nothing();

    void Run();

private:
    DxUi* _ui;
    IUiProperty* _uiProperty;
    IMsgMgr* _msgMgr;
    MsgTest* _test;
};

#endif // UI_NOTHING_H
