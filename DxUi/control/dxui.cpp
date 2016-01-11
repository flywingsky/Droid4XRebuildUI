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
        PageData d;
        d.title = QString::number(n);
        p->AddPage(d);
    }
    p->show();

}

MainPanel* DxUi::CreatePanel()
{
    MainPanel* p = new MainPanel();
    connect(p, SIGNAL(DragOut(QListWidgetItem*)), this, SLOT(DragOutCreate(QListWidgetItem*)));
    return p;
}

void DxUi::DragOutCreate(QListWidgetItem *it)
{
    MainPanel* p = CreatePanel();
    PageData d = SwitchableListWidget::GetPageData(it);
    p->AddPage(d);
    p->move(QCursor::pos());
    p->show();
}

