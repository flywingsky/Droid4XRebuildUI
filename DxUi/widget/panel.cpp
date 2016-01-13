#include "page.h"
#include "panel.h"
#include "mainpanel.h"
#include "pagedata.h"
#include "title.h"

#include <QDebug>

Panel::Panel(QWidget *parent) : QStackedWidget(parent)
{

}

void Panel::AddPage(PageData* d)
{
    Page* p = new Page(this);
    p->TitleWidget()->SetMainPanel(d->mainPanel);
    connect(p->TitleWidget(), SIGNAL(MinWnd()), d->mainPanel, SLOT(showMinimized()));
    connect(p->TitleWidget(), SIGNAL(MaxWnd()), d->mainPanel, SLOT(showMaximized()));
    connect(p->TitleWidget(), SIGNAL(NormalWnd()), d->mainPanel, SLOT(showNormal()));
    connect(p->TitleWidget(), SIGNAL(CloseWnd()), d->mainPanel, SLOT(close()));
    p->TitleWidget()->SetMoveTarget(d->mainPanel);
    p->TitleWidget()->SetText(d->title);

    d->index = addWidget(p);
    d->page = p;

}

Page *Panel::CurrentPage()
{
    return (Page*)currentWidget();
}



