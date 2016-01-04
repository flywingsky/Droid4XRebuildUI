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


MainPanel::MainPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPanel),
    _fSize(new FramelessResize(this))
{
    ui->setupUi(this);

    FramelessMove::SetFrameLess(true,this);

    _fSize->SetMonitor(this);
    connect(_fSize, SIGNAL(OffsetGeometry(QMargins)), this, SLOT(OffsetSize(QMargins)));



    _splitter = new QSplitter(this);
    _splitter->addWidget(ui->listWidget);
    _splitter->addWidget(ui->pannel);
    _splitter->setHandleWidth(10);
    _splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    _splitter->show();


    connect(ui->listWidget, SIGNAL(ActiveIndex(int)), ui->pannel, SLOT(setCurrentIndex(int)));

    setLayout(new QGridLayout(this));
    layout()->addWidget(_splitter);
    _fSize->SetBorderWidth(layout()->margin());

}

MainPanel::~MainPanel()
{
    delete ui;
}

int MainPanel::AddPage(Page *p)
{
    connect(p->TitleWidget(), SIGNAL(MinWnd()), this, SLOT(showMinimized()));
    connect(p->TitleWidget(), SIGNAL(MaxWnd()), this, SLOT(showMaximized()));
    connect(p->TitleWidget(), SIGNAL(NormalWnd()), this, SLOT(showNormal()));
    connect(p->TitleWidget(), SIGNAL(CloseWnd()), this, SLOT(close()));
    p->TitleWidget()->SetMoveTarget(this);

    PageData d;
    d.index = ui->pannel->addWidget(p);
    d.title = QString::number(d.index);

    p->TitleWidget()->SetText(d.title);
    ui->listWidget->AppendItem(d);

    return d.index;
}

void MainPanel::OffsetSize(QMargins g)
{
    setGeometry(geometry() + g);
}


