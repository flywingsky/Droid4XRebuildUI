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
        setWindowState(Qt::WindowNoState);
        QApplication::processEvents();
        move(QCursor::pos() - QPoint(ui->title->width()/2,ui->title->height()/2));
    }
    else
        move(pos() + offset);
}
