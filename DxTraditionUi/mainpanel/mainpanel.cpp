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
#include "screen.h"
#include <QApplication>
#include <QResizeEvent>
#include "UIMsgMgr.h"
#include "msgdef.h"

MainPanel::MainPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPanel),
    _move(new FramelessMove),
    _resize(new FramelessResize),
    _focus(NULL),
    _toolbar(NULL),
    _normalLandscape(NULL),
    _normalPortrait(NULL),
    _normalPos(NULL),
    _rotate(0)

//    _normalLandscape(QRect(100,100,1000,1000)),
//    _normalPortrait(100,100,453,707)
{
    ui->setupUi(this);

    FramelessMove::SetFrameLess(true, this);
    _resize->SetMonitor(this);
    _resize->SetTarget(this);
    _resize->SetBorderWidth(layout()->margin());

    InitTitle();
    InitFocusWidget();
    installEventFilter(this);
    ui->client->installEventFilter(this);
    ui->client->GetScreen()->installEventFilter(this);


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
    _scale = s;
//    Q_ASSERT(_resize);
//    _resize->SetScale(s,ui->client);
}

QSize MainPanel::Scale() const
{
    Q_ASSERT(_resize);
    return _resize->Scale();
}

void MainPanel::SetToolbar(ToolBar *t)
{

    if(t)
    {
        connect(t->GetButton("full"), SIGNAL(clicked()), this, SLOT(ReverseFullStatus()));
        t->installEventFilter(this);
    }
    else
    {
        if(_toolbar)
        {
            _toolbar->removeEventFilter(this);
        }
    }
    _toolbar = t;

}

void MainPanel::SetRotate(int r)
{
    _rotate = r;
}


void MainPanel::Rescale()
{
    int min = qMin(_scale.width(),_scale.height());
    int max = qMax(_scale.width(),_scale.height());

    bool portrait = bool(_rotate%180);

    qDebug() << max << min;

    _toolbar->StopAutoFloat();

    if(Qt::WindowNoState == windowState())
    {
        _resize->SetScale(portrait ? QSize(min,max) : QSize(max, min), (QWidget*)ui->client);

        ui->client->SetScale(portrait ? QSize(min,max) : QSize(max, min));
        ui->client->SetScale(QSize());
        SetToolbarDockArea(portrait ? Qt::LeftDockWidgetArea : Qt::BottomDockWidgetArea);

        if(portrait && !_normalPortrait)
            InitNormalSize(true, QSize(min,max));
        else if(!portrait && !_normalLandscape)
            InitNormalSize(false, QSize(max, min));

        setGeometry(QRect(*_normalPos, (portrait ? *_normalPortrait : *_normalLandscape)));
    }
    else
    {
        _resize->SetScale(portrait ? QSize(min,max) : QSize(max, min), (QWidget*)ui->client->GetScreen());

        ui->client->SetScale(portrait ? QSize(min,max) : QSize(max, min));

        if(Qt::WindowFullScreen == windowState())
        {
            SetWithoutToolbarLayout(windowState());
            _toolbar->SetAutoFloat(this);
        }
        else
            SetToolbarDockArea(portrait ? Qt::LeftDockWidgetArea : Qt::BottomDockWidgetArea);
    }

}

void MainPanel::SetLandscape()
{
    SetRotate(0);
    Rescale();
}

void MainPanel::SetPortrait()
{
    SetRotate(90);
    Rescale();

}



void MainPanel::ReverseMaxStatus()
{
    setWindowState(isMaximized() ? Qt::WindowNoState : Qt::WindowMaximized);
}

void MainPanel::ReverseFullStatus()
{
    setWindowState(isFullScreen() ? Qt::WindowNoState : Qt::WindowFullScreen);
    isFullScreen() ? ui->title->hide() : ui->title->show();
}

void MainPanel::resizeEvent(QResizeEvent *event)
{
    RecodeNormalSize();
}

void MainPanel::moveEvent(QMoveEvent *event)
{
    if(Qt::WindowNoState == windowState() && _normalPos)
        *_normalPos = event->pos();
}

void MainPanel::changeEvent(QEvent *event)
{

    if(event->type() == QEvent::WindowStateChange)
    {
        ReverseTitleMaxBtn();
        Rescale();


        if(Qt::WindowNoState == windowState())
        {
            layout()->setMargin(3);
            _resize->SetBorderWidth(3);
        }
        else
        {
            layout()->setMargin(0);
            _resize->SetBorderWidth(0);
        }

    }
}

bool MainPanel::event(QEvent * e)
{
    return QWidget::event(e);
}

bool MainPanel::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == _toolbar ||
            obj == ui->title ||
            obj == ui->client ||
            obj == ui->client->GetScreen())
    {
        if(ev->type() == QEvent::MouseButtonPress)
            _focus->setFocus();
    }
    return QWidget::eventFilter(obj, ev);
}

void MainPanel::closeEvent(QCloseEvent *event)
{
    CUIMsgMgr::Post(State::Close,NULL,NULL);
    QDialog::closeEvent(event);
}


void MainPanel::InitTitle()
{
    _move->SetMonitor(ui->title);
    ui->title->installEventFilter(this);

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
        putin.append(CommonFunc::LayoutWidget(ui->title,QRect(0,0,1,2)));
        putin.append(CommonFunc::LayoutWidget(_toolbar,QRect(1,0,1,1)));
        putin.append(CommonFunc::LayoutWidget(ui->client,QRect(1,1,1,1)));
        _toolbar->SetPortrait();
        break;
    case Qt::BottomDockWidgetArea:
        putin.append(CommonFunc::LayoutWidget(ui->title,QRect(0,0,1,1)));
        putin.append(CommonFunc::LayoutWidget(ui->client,QRect(1,0,1,1)));
        putin.append(CommonFunc::LayoutWidget(_toolbar,QRect(2,0,1,1)));
        _toolbar->SetLandscape();
        break;
    default:
        putin.append(CommonFunc::LayoutWidget(ui->title,QRect(0,0,1,1)));
        putin.append(CommonFunc::LayoutWidget(ui->client,QRect(1,0,1,1)));
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
        putin.append(CommonFunc::LayoutWidget(ui->client,QRect(0,0,1,1)));
        break;
    case Qt::WindowMaximized:
        putin.append(CommonFunc::LayoutWidget(ui->title,QRect(0,0,1,1)));
        putin.append(CommonFunc::LayoutWidget(ui->client,QRect(1,0,1,1)));
        break;
    default:
        putin.append(CommonFunc::LayoutWidget(ui->title,QRect(0,0,1,1)));
        putin.append(CommonFunc::LayoutWidget(ui->client,QRect(1,0,1,1)));
        break;
    }
    CommonFunc::Relayout(putin, (QGridLayout*)layout());
}

void MainPanel::ReverseTitleMaxBtn()
{
    if(windowState() == Qt::WindowNoState)
        ui->title->GetButton("max")->setChecked(false);
    else
        ui->title->GetButton("max")->setChecked(true);
}

void MainPanel::InitNormalSize(bool Portrait, QSize scale)
{
    const int screenFrame = 300;
    QRect screen = CommonFunc::PrimaryScreenGeometry();
    QSize t = screen.size() - QSize(screenFrame,screenFrame);
    int max = qMax(t.width(),t.height());
    int min = qMin(t.width(), t.height());

    QApplication::processEvents();
    QSize fix = size() - ui->client->size();

    QSize temp = Portrait ? QSize(min, max) : QSize(min, max);
    temp = CommonFunc::CenterRect(screen, temp.scaled(t, Qt::KeepAspectRatio)).size();
    temp = fix + scale.scaled(temp,Qt::KeepAspectRatioByExpanding);
    QRect rc = CommonFunc::CenterRect(screen,temp);
    if(!_normalPos)
        _normalPos = new QPoint();
    *_normalPos = rc.topLeft();

    if(Portrait)
    {
        if(!_normalPortrait)
            _normalPortrait = new QSize();
        *_normalPortrait = rc.size();
    }
    else
    {
        if(!_normalLandscape)
            _normalLandscape = new QSize();
        *_normalLandscape = rc.size();
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

void MainPanel::RecodeNormalSize()
{
    if(windowState() == Qt::WindowNoState)
    {
        if(CommonFunc::IsLandscape((QWidget*)ui->client->GetScreen()))
        {
            if(_normalLandscape && CommonFunc::IsLandscape(size()))
                *_normalLandscape = size();
        }
        else
        {
            if(_normalPortrait && !CommonFunc::IsLandscape(size()))
                *_normalPortrait = size();
        }
    }
}
