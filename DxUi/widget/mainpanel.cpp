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
    _fixRatio(50,50)
{
    ui->setupUi(this);


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


    connect(ui->listWidget, SIGNAL(ActivePage(QWidget*)), ui->panel, SLOT(setCurrentWidget(QWidget*)));
    connect(ui->listWidget, SIGNAL(DragLeave(PageData*)), ui->panel, SLOT(DeletePage(PageData*)));
    connect(ui->listWidget, SIGNAL(DragEnter(PageData*)), ui->panel, SLOT(AddPage(PageData*)));
    connect(ui->listWidget, SIGNAL(DragOut(PageData*)), this, SIGNAL(DragOut(PageData*)));

    connect(ui->panel, SIGNAL(Empty()), this, SLOT(close()));

    setLayout(new QGridLayout(this));
    layout()->addWidget(_splitter);
    _fSize->SetBorderWidth(layout()->margin());

}

MainPanel::~MainPanel()
{
    delete ui;
}

void MainPanel::AddPage(PageData* d)
{
    ui->panel->AddPage(d);
    ui->listWidget->AppendItem(d);
}

QMargins MainPanel::FixRatioTransform(const QMargins &g)
{
    if(g.isNull())
        return g;
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
