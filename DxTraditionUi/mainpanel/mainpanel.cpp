#include "mainpanel.h"
#include "ui_mainpanel.h"

#include <QPushButton>
#include "framelessmove.h"
#include "framelessresize.h"
#include "focuswidget.h"
#include <QDebug>
#include "qss.h"
#include "commonfunc.h"
#include "toolbar.h"

MainPanel::MainPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPanel),
    _move(new FramelessMove),
    _resize(new FramelessResize),
    _focus(NULL),
    _toolbar(NULL),
    _normalLandscape(QRect(100,100,1178,688)),
    _normalPortrait(100,100,447,780)
{
    ui->setupUi(this);
    FramelessMove::SetFrameLess(true, this);
    _resize->SetMonitor(this);
    _resize->SetTarget(this);
    _resize->SetBorderWidth(layout()->margin());
    InitTitle();
    InitFocusWidget();


}

MainPanel::~MainPanel()
{
    delete ui;
}

Screen *MainPanel::GetScreen() const
{
    return ui->client->GetScreen();
}

void MainPanel::SetScale(QSize s)
{
    Q_ASSERT(_resize);
    _resize->SetScale(s,ui->client);
}

void MainPanel::SetToolbar(ToolBar *t)
{
    _toolbar = t;

}

void MainPanel::SetRotate(int r)
{
    int min = qMin(_resize->Scale().width(),_resize->Scale().height());
    int max = qMax(_resize->Scale().width(),_resize->Scale().height());

    bool portrait = bool(r%180);

    if(Qt::WindowNoState == windowState())
    {
        ui->client->SetScale(QSize());
        SetToolbarDockArea(portrait ? Qt::LeftDockWidgetArea : Qt::BottomDockWidgetArea);
        setGeometry(portrait ? _normalPortrait : _normalLandscape);
    }
    else
    {
        ui->client->SetScale(portrait ? QSize(min,max) : QSize(max, min));
        SetWithoutToolbarLayout(windowState());
    }
}

void MainPanel::SetLandscape()
{
    SetRotate(0);
}

void MainPanel::SetPortrait()
{
    SetRotate(90);

}



void MainPanel::ReverseMaxStatus()
{
    setWindowState(isMaximized() ? Qt::WindowNoState : Qt::WindowMaximized);
}


void MainPanel::resizeEvent(QResizeEvent *event)
{
    RecodeNormalSize();
}

void MainPanel::moveEvent(QMoveEvent *event)
{
    RecodeNormalSize();
}

void MainPanel::changeEvent(QEvent *event)
{

    if(event->type() == QEvent::WindowStateChange)
    {
        bool landscape = CommonFunc::IsLandscape((QWidget*)ui->client->GetScreen());
        SetRotate(landscape ? 0 : 90);

        if(Qt::WindowNoState == windowState())
            layout()->setMargin(3);
        else
            layout()->setMargin(0);

    }
}

void MainPanel::InitTitle()
{
    _move->SetMonitor(ui->title);

    connect(_move, SIGNAL(Offset(QPoint)), this, SLOT(DragMove(QPoint)));
    connect(ui->title->GetButton("close"), SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->title->GetButton("max"), SIGNAL(clicked()), this, SLOT(ReverseMaxStatus()));
    connect(ui->title->GetButton("min"), SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(ui->title->GetButton("at"), SIGNAL(clicked()), this, SLOT(SetLandscape()));
    connect(ui->title->GetButton("set"), SIGNAL(clicked()), this, SLOT(SetPortrait()));
    connect(ui->title, SIGNAL(DoubleClicked()), this, SLOT(ReverseMaxStatus()));


}

void MainPanel::InitFocusWidget()
{
    _focus = new FocusWidget(this);
    _focus->resize(100,100);
    _focus->move(width() - _focus->width(), height() - _focus->height());
    _focus->setFocus();
    _focus->lower();

}

void MainPanel::SetToolbarDockArea(Qt::DockWidgetArea postion)
{
    Q_ASSERT(_toolbar);

    CommonFunc::LayoutItems putin;
    switch(postion)
    {
    case Qt::LeftDockWidgetArea:
        putin.append(CommonFunc::LayoutItem(ui->title,QRect(0,0,1,2)));
        putin.append(CommonFunc::LayoutItem(_toolbar,QRect(1,0,1,1)));
        putin.append(CommonFunc::LayoutItem(ui->client,QRect(1,1,1,1)));
        _toolbar->SetPortrait();
        break;
    case Qt::BottomDockWidgetArea:
        putin.append(CommonFunc::LayoutItem(ui->title,QRect(0,0,1,1)));
        putin.append(CommonFunc::LayoutItem(ui->client,QRect(1,0,1,1)));
        putin.append(CommonFunc::LayoutItem(_toolbar,QRect(2,0,1,1)));
        _toolbar->SetLandscape();
        break;
    default:
        putin.append(CommonFunc::LayoutItem(ui->title,QRect(0,0,1,1)));
        putin.append(CommonFunc::LayoutItem(ui->client,QRect(1,0,1,1)));
        break;

    }

    CommonFunc::Relayout(putin, (QGridLayout*)layout());


}

void MainPanel::SetWithoutToolbarLayout(Qt::WindowStates ws)
{
    CommonFunc::LayoutItems putin;
    switch(ws)
    {
    case Qt::WindowFullScreen:
        putin.append(CommonFunc::LayoutItem(ui->client,QRect(0,0,1,1)));
        break;
    case Qt::WindowMaximized:
        putin.append(CommonFunc::LayoutItem(ui->title,QRect(0,0,1,1)));
        putin.append(CommonFunc::LayoutItem(ui->client,QRect(1,0,1,1)));
        break;
    default:
        putin.append(CommonFunc::LayoutItem(ui->title,QRect(0,0,1,1)));
        putin.append(CommonFunc::LayoutItem(ui->client,QRect(1,0,1,1)));
        break;
    }
    CommonFunc::Relayout(putin, (QGridLayout*)layout());
}


void MainPanel::DragMove(QPoint offset)
{
    if(windowState() != Qt::WindowNoState)
    {
        QSize sMax = size();
        QPoint pMax = pos();

        setWindowState(Qt::WindowNoState);
        QApplication::processEvents();

        // 这一大段是用数学公式算出来的，目的就是让鼠标放在等比的位置上
        int x = (1.0-(qreal)width()/sMax.width())*QCursor::pos().x() + pMax.x()*(qreal)width()/sMax.width();
        int y = pMax.y() + offset.y();

        move(x,y);
    }
    else
        move(pos() + offset);
}

void MainPanel::RecodeNormalSize()
{
    if(windowState() == Qt::WindowNoState)
    {
        if(CommonFunc::IsLandscape((QWidget*)ui->client->GetScreen()))
            _normalLandscape = geometry();
        else
            _normalPortrait = geometry();
    }
}
