#include "itemwidget.h"
#include "ui_itemwidget.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPropertyAnimation>

#include "framelessmove.h"
ItemWidget::ItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget),
    _frame(new FramelessMove(this)),
    _it(NULL)
{
    ui->setupUi(this);
    _frame->SetMonitor(this);
    connect(_frame, SIGNAL(Offset(QPoint)), this, SLOT(Move(QPoint)));
    connect(_frame, SIGNAL(Pressed(QPoint)), this, SLOT(raise()));
    connect(_frame, SIGNAL(Pressed(QPoint)), this, SIGNAL(Pressed()));
}

ItemWidget::~ItemWidget()
{
    delete ui;
}


void ItemWidget::SetText(QString t)
{
    ui->label->setText(t);
}

void ItemWidget::SaveItem(QListWidgetItem *it)
{
    _it = it;
}

QListWidgetItem *ItemWidget::Item()
{
    return _it;
}


void ItemWidget::Move(QPoint pt)
{
    pt.setX(0);
    move(pos() + pt);
}
