#include "mainpanel.h"
#include "ui_mainpanel.h"

#include <QPushButton>
#include "framelessmove.h"
#include "framelessresize.h"
#include "focuswidget.h"
#include <QDebug>
#include "qss.h"
#include "commonfunc.h"

MainPanel::MainPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPanel),
    _move(new FramelessMove),
    _resize(new FramelessResize),
    _focus(NULL),
    _toolbar(NULL)
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
    return ui->screen;
}

void MainPanel::SetScale(QSize s)
{
    Q_ASSERT(_resize);
    _resize->SetScale(s,ui->screen);
}

void MainPanel::SetToolbar(QWidget *t)
{
    _toolbar = t;

    RelayoutToolbar();
}



void MainPanel::ReverseMaxStatus()
{
    setWindowState(isMaximized() ? Qt::WindowNoState : Qt::WindowMaximized);
}


void MainPanel::resizeEvent(QResizeEvent *event)
{
    RelayoutToolbar();
}

void MainPanel::InitTitle()
{
    _move->SetMonitor(ui->title);

    connect(_move, SIGNAL(Offset(QPoint)), this, SLOT(DragMove(QPoint)));
    connect(ui->title->GetButton("close"), SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->title->GetButton("max"), SIGNAL(clicked()), this, SLOT(ReverseMaxStatus()));
    connect(ui->title->GetButton("min"), SIGNAL(clicked()), this, SLOT(showMinimized()));
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
    typedef QPair<QWidget*, QRect> LItem;
    QList<LItem> putin;
    switch(postion)
    {
    case Qt::LeftDockWidgetArea:
        putin.append(LItem(ui->title,QRect(0,0,1,2)));
        putin.append(LItem(_toolbar,QRect(1,0,1,1)));
        putin.append(LItem(ui->screen,QRect(1,1,1,1)));
        break;
    case Qt::BottomDockWidgetArea:
        putin.append(LItem(ui->title,QRect(0,0,1,1)));
        putin.append(LItem(ui->screen,QRect(1,0,1,1)));
        putin.append(LItem(_toolbar,QRect(2,0,1,1)));
        break;
    case Qt::RightDockWidgetArea:
        putin.append(LItem(ui->title,QRect(0,0,1,2)));
        putin.append(LItem(ui->screen,QRect(1,0,1,1)));
        putin.append(LItem(_toolbar,QRect(1,1,1,1)));
        break;
    case Qt::TopDockWidgetArea:
        putin.append(LItem(ui->title,QRect(0,0,1,1)));
        putin.append(LItem(_toolbar,QRect(1,0,1,1)));
        putin.append(LItem(ui->screen,QRect(2,0,1,1)));
        break;
    default:
        putin.append(LItem(ui->title,QRect(0,0,1,1)));
        putin.append(LItem(ui->screen,QRect(1,0,1,1)));
        break;

    }

    CommonFunc::ClearLayout(layout());
    QGridLayout* l = (QGridLayout*)layout();

    foreach (LItem item, putin) {
        l->addWidget(item.first,item.second.x(),item.second.y(),item.second.width(),item.second.height());
    }
}

void MainPanel::RelayoutToolbar()
{
    if(_toolbar)
    {
        if(CommonFunc::IsLandscape(this))
            SetToolbarDockArea(Qt::BottomDockWidgetArea);
        else
            SetToolbarDockArea(Qt::LeftDockWidgetArea);
    }
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
