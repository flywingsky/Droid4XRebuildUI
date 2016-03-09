#include "screen.h"
#include "ui_screen.h"

#include "UIMsgMgr.h"

#include "msgdef.h"

#include <QMouseEvent>

Screen::Screen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Screen)
{
    ui->setupUi(this);
}

Screen::~Screen()
{
    delete ui;
}

void Screen::mousePressEvent(QMouseEvent * event)
{
    IMsgMgr* msg = CUIMsgMgr::GetMsgMgr();
    static QPoint pt(event->pos());

    msg->PostMsg(InOut::MousePress,&pt,NULL);

    QWidget::mousePressEvent(event);
}

void Screen::mouseReleaseEvent(QMouseEvent *event)
{
    IMsgMgr* msg = CUIMsgMgr::GetMsgMgr();
    static QPoint pt(event->pos());

    msg->PostMsg(InOut::MouseRelease,&pt,NULL);
    QWidget::mouseReleaseEvent(event);
}

void Screen::mouseMoveEvent(QMouseEvent *event)
{
    IMsgMgr* msg = CUIMsgMgr::GetMsgMgr();
    static QPoint pt(event->pos());

    msg->PostMsg(InOut::MouseMove,&pt,NULL);
    QWidget::mouseMoveEvent(event);
}

void Screen::resizeEvent(QResizeEvent *event)
{
    ui->label->setText(QString::number((double)width() / height()));
    QWidget::resizeEvent(event);
}
