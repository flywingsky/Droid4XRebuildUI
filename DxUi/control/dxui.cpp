#include "dxui.h"

#include "mainpanel.h"
#include "pagedata.h"
#include "defprivate.h"
#include "switchablelistwidget.h"
#include "page.h"

#include <QListWidgetItem>
#include <QDebug>

DxUi::DxUi(QObject *parent) :
    QObject(parent)
{

}

MainPanel* DxUi::CreatePanel()
{
    MainPanel* p = new MainPanel();
    connect(p, SIGNAL(DragOut(PageData*)), this, SLOT(DragOutCreate(PageData*)));
    return p;
}

void DxUi::AddPage(MainPanel *p, PageData *d)
{
    p->AddPage(d);
    _datas.append(d);
}

void DxUi::DragOutCreate(PageData* d)
{
    MainPanel* p = CreatePanel();
    AddPage(p,d);
    p->move(QCursor::pos());
    p->show();
}

