#ifndef DXUI_H
#define DXUI_H

#include "dllpro_global.h"

class IMsgMgr;


class DLLPROSHARED_EXPORT DxUi
{
public:
    static IMsgMgr* GetMsgMgr();
public:
    DxUi();

    void CreateMainWnd();

};

#endif // DXUI_H
