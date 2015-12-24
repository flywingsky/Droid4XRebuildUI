#include "mainpanel.h"
#include "ui_mainpanel.h"

#include <windows.h>
#include <QDebug>
#include <QSplitter>
#include "framelessmove.h"

MainPanel::MainPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPanel),
    _frameMgr(new FramelessMove(this))
{
    ui->setupUi(this);

    connect(ui->title, SIGNAL(MinWnd()), this, SLOT(showMinimized()));
    connect(ui->title, SIGNAL(MaxWnd()), this, SLOT(showMaximized()));
    connect(ui->title, SIGNAL(NormalWnd()), this, SLOT(showNormal()));
    connect(ui->title, SIGNAL(CloseWnd()), this, SLOT(close()));

    _frameMgr->SetMonitor(ui->title);
    _frameMgr->SetTarget(this);
    //_frameMgr->SetFrameLess(true);
    ui->title->installEventFilter(ui->title);



    _splitter = new QSplitter(this);
    _splitter->addWidget(ui->listWidget);
    _splitter->addWidget(ui->pannel);
    _splitter->setHandleWidth(10);
    _splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    _splitter->show();


    setLayout(new QGridLayout(this));
    layout()->addWidget(_splitter);



}

MainPanel::~MainPanel()
{
    delete ui;
}


