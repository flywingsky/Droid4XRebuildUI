#include "bubblegum.h"
#include "ui_bubblegum.h"

#include "framelessmove.h"
#include "defprivate.h"

#include <QPainter>
#include <QDebug>

BubbleGum::BubbleGum(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::BubbleGum),
    _fm(new FramelessMove(this)),
    _radius(GUM_RADIUS)
{
    ui->setupUi(this);
    FramelessMove::SetFrameLess(true,this);
    _fm->SetMonitor(this);
    _fm->SetTarget(this);

    connect(_fm, SIGNAL(Offset(QPoint)), this, SLOT(DragMove(QPoint)));
    connect(_fm, SIGNAL(Pressed(QPoint)), this, SLOT(Pressed(QPoint)));
    connect(_fm, SIGNAL(Release(QPoint)), this, SLOT(Released(QPoint)));
}

BubbleGum::~BubbleGum()
{
    delete ui;
}

void BubbleGum::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
//    QPainter p(this);

//    p.setRenderHint(QPainter::Antialiasing);

//    p.setPen(QPen(QColor(QString("#ff0000"))));
//    p.setBrush(QBrush(QColor(QString("#ff0000"))));

//    p.drawEllipse((QPointF)rect().center(),_radius,_radius);
}

void BubbleGum::DragMove(QPoint pos)
{
    _dragPos += pos;
    _radius = GUM_RADIUS - (_dragPos - rect().center()).manhattanLength() / 5.0;
    update();
}

void BubbleGum::Pressed(QPoint pos)
{
    _dragPos = rect().center();
}

void BubbleGum::Released(QPoint pos)
{
    _dragPos = QPoint(0,0);
    _radius = GUM_RADIUS;
    update();
}
