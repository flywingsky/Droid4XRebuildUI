#include "mainpanel.h"
#include "ui_mainpanel.h"

#include <QPushButton>
#include "framelessmove.h"
#include "framelessresize.h"

MainPanel::MainPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPanel),
    _move(new FramelessMove),
    _resize(new FramelessResize)
{
    ui->setupUi(this);
    FramelessMove::SetFrameLess(true, this);
    _resize->SetMonitor(this);
    _resize->SetTarget(this);
    _resize->SetBorderWidth(layout()->margin());
    InitTitle();
}

MainPanel::~MainPanel()
{
    delete ui;
}

void MainPanel::ReverseMaxStatus()
{
    setWindowState(isMaximized() ? Qt::WindowNoState : Qt::WindowMaximized);
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
