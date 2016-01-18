#include "itemwidget.h"
#include "ui_itemwidget.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPropertyAnimation>

#include "framelessmove.h"
#include "snapshotpage.h"

ItemWidget::ItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget),
    _frame(new FramelessMove(this))
{
    ui->setupUi(this);
    _frame->SetMonitor(this);
    connect(_frame, SIGNAL(Pressed(QPoint)), this, SLOT(raise()));
    connect(_frame, SIGNAL(Pressed(QPoint)), this, SIGNAL(Pressed()));
}

ItemWidget::~ItemWidget()
{
    qDebug() << "~ItemWidget";
    delete ui;
}


void ItemWidget::SetText(QString t)
{
    ui->label->setText(t);
}

QString ItemWidget::Text() const
{
    return ui->label->text();
}



