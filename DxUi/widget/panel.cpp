#include "page.h"
#include "panel.h"
#include "mainpanel.h"
#include "pagedata.h"
#include "title.h"

#include <QDebug>

Panel::Panel(QWidget *parent) :
    QStackedWidget(parent),
    _panel((MainPanel*) parent)
{

}


Page *Panel::CurrentPage()
{
    return (Page*)currentWidget();
}


void Panel::AddPage(PageData* d)
{
    Page* p = d->page;
    if(!p)
        p = new Page(this);

    p->TitleWidget()->SetMainPanel(_panel);
    connect(p->TitleWidget(), SIGNAL(MinWnd()), _panel, SLOT(showMinimized()));
    connect(p->TitleWidget(), SIGNAL(MaxWnd()), _panel, SLOT(showMaximized()));
    connect(p->TitleWidget(), SIGNAL(NormalWnd()), _panel, SLOT(showNormal()));
    connect(p->TitleWidget(), SIGNAL(CloseWnd()), _panel, SLOT(close()));
    p->TitleWidget()->SetMoveTarget(_panel);
    p->TitleWidget()->SetText(d->title);

    addWidget(p);
    setCurrentWidget(p);
    d->page = p;

}

void Panel::DeletePage(PageData *d)
{
    Page* p = d->page;
    p->TitleWidget()->SetMainPanel(NULL);
    disconnect(p->TitleWidget(), SIGNAL(MinWnd()), _panel, SLOT(showMinimized()));
    disconnect(p->TitleWidget(), SIGNAL(MaxWnd()), _panel, SLOT(showMaximized()));
    disconnect(p->TitleWidget(), SIGNAL(NormalWnd()), _panel, SLOT(showNormal()));
    disconnect(p->TitleWidget(), SIGNAL(CloseWnd()), _panel, SLOT(close()));
    p->TitleWidget()->SetMoveTarget(NULL);

    removeWidget(p);

    if(count() < 1)
        emit Empty();
}


