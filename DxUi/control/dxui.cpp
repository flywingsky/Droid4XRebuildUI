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
    MainPanel* p = CreatePanel();
    QString s;
    for(int n=0; n<10; ++n)
    {
        PageData* d = new PageData;
        d->title = QString::number(n) + QString::number((int)d);
        p->AddPage(d);
        _datas.append(d);
    }
    p->show();

}

MainPanel* DxUi::CreatePanel()
{
    MainPanel* p = new MainPanel();
    connect(p, SIGNAL(DragOut(PageData*)), this, SLOT(DragOutCreate(PageData*)));
    return p;
}

void DxUi::DragOutCreate(PageData* d)
{
    MainPanel* p = CreatePanel();
    p->AddPage(d);
    p->move(QCursor::pos());
    p->show();
    _datas.append(d);
}

