#include "dxui.h"

#include "mainpanel.h"
#include "page.h"

DxUi::DxUi(QObject *parent) :
    QObject(parent)
{
    MainPanel* p = new MainPanel();
    for(int n=0; n<10; ++n)
    {
        p->AddPage(new Page(p));
    }
    p->show();
}
