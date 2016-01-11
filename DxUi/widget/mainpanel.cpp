#include "mainpanel.h"
#include "ui_mainpanel.h"

#include <windows.h>
#include <QDebug>
#include <QSplitter>
#include <QGridLayout>
#include "pagedata.h"
#include "framelessmove.h"
#include "page.h"
#include "title.h"
#include "framelessresize.h"
#include "snapshotpage.h"
#include "pagedata.h"
#include "screen.h"


MainPanel::MainPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPanel),
    _fSize(new FramelessResize(this)),
    _fixRatio(50,25)
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(DragOut(QListWidgetItem*)), this, SIGNAL(DragOut(QListWidgetItem*)));

    FramelessMove::SetFrameLess(true,this);

    _fSize->SetMonitor(this);
    connect(_fSize, SIGNAL(OffsetGeometry(QMargins)), this, SLOT(OffsetSize(QMargins)));



    _splitter = new QSplitter(this);
    _splitter->addWidget(ui->listWidget);
    _splitter->addWidget(ui->panel);
    _splitter->setStretchFactor(1,1);
    _splitter->setHandleWidth(10);
    _splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    _splitter->show();


    connect(ui->listWidget, SIGNAL(ActiveIndex(int)), ui->panel, SLOT(setCurrentIndex(int)));

    setLayout(new QGridLayout(this));
    layout()->addWidget(_splitter);
    _fSize->SetBorderWidth(layout()->margin());

}

MainPanel::~MainPanel()
{
    delete ui;
}

int MainPanel::AddPage(PageData& d)
{
    Page* p = new Page(this);
    p->TitleWidget()->SetMainPanel(this);
    connect(p->TitleWidget(), SIGNAL(MinWnd()), this, SLOT(showMinimized()));
    connect(p->TitleWidget(), SIGNAL(MaxWnd()), this, SLOT(showMaximized()));
    connect(p->TitleWidget(), SIGNAL(NormalWnd()), this, SLOT(showNormal()));
    connect(p->TitleWidget(), SIGNAL(CloseWnd()), this, SLOT(close()));
    p->TitleWidget()->SetMoveTarget(this);

    d.index = ui->panel->addWidget(p);
    d.page = p;

    p->TitleWidget()->SetText(d.title);
    ui->listWidget->AppendItem(d);








    return d.index;
}

QMargins MainPanel::FixRatioTransform(const QMargins &g)
{
    Screen* s = ui->panel->CurrentPage()->ScreenWidget();

    QSize intend = (s->geometry() + g).size();

    int sum = g.left()+g.top()+g.right()+g.bottom();
    QSize except = _fixRatio.scaled(intend, (sum > 0 ? Qt::KeepAspectRatioByExpanding : Qt::KeepAspectRatio)) - s->size();

    QMargins ret;

    qreal h = g.left() + g.right();
    qreal v = g.top() + g.bottom();

    if(h)
    {
        ret.setLeft(g.left() / h * except.width());
        ret.setRight(g.right() / h * except.width());
    }
    else
        ret.setRight(except.width());

    if(v)
    {
        ret.setTop(g.top() / v * except.height());
        ret.setBottom(g.bottom() / v * except.height());
    }
    else
        ret.setBottom(except.height());


    return ret;

}


void MainPanel::OffsetSize(QMargins g)
{
    setGeometry(geometry() + FixRatioTransform(g));
}
