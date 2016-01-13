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
    _frame(new FramelessMove(this)),
    _snappage(NULL)
{
    ui->setupUi(this);
    _frame->SetMonitor(this);
    connect(_frame, SIGNAL(Offset(QPoint)), this, SLOT(Move(QPoint)));
    connect(_frame, SIGNAL(Offset(QPoint)), this, SIGNAL(Offset(QPoint)));
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



void ItemWidget::ShowSnap(QWidget* snapWidget)
{
    if(snapWidget)
    {
        // show
        if(!_snappage)
            _snappage = new SnapshotPage();
        _snappage->SetWidget(snapWidget);
        _snappage->move(QCursor::pos() - QPoint(_snappage->width() / 2, 10));
        _snappage->show();
        _snappage->raise();

    }
    else
    {
        // hide
        if(_snappage)
        {
            _snappage->hide();
            delete _snappage;
        }
        _snappage = NULL;
    }


}

bool ItemWidget::IsSnapHidden()
{
    return (_snappage ? _snappage->isHidden() : true);
}



void ItemWidget::Move(QPoint pt)
{
    if(_snappage)
        _snappage->move(QCursor::pos() - QPoint(_snappage->width() / 2, 10));
}
