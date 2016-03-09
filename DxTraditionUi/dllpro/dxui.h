#ifndef DXUI_H
#define DXUI_H

#include "dllpro_global.h"

#include <QtGlobal>

class IMsgMgr;
class DxUiPrivate;
class IUiProperty;

class DLLPROSHARED_EXPORT DxUi
{
public:
    static IMsgMgr* GetMsgMgr();
public:
    DxUi();

    void CreateMainWnd();

    IUiProperty* GetProperty() const;



protected:
    DxUi(DxUiPrivate* dd);

private:
    DxUiPrivate* d_ptr;
    Q_DECLARE_PRIVATE(DxUi)

};

#endif // DXUI_H
