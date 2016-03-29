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
    static QPoint pt;
    pt = event->pos();
    CUIMsgMgr::Post(InOut::MousePress,&pt,NULL);

    QWidget::mousePressEvent(event);
}

void Screen::mouseReleaseEvent(QMouseEvent *event)
{
    static QPoint pt;
    pt = event->pos();
    CUIMsgMgr::Post(InOut::MouseRelease,&pt,NULL);
    QWidget::mouseReleaseEvent(event);
}

void Screen::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint pt;
    pt = event->pos();
    CUIMsgMgr::Post(InOut::MouseMove,&pt,NULL);
    QWidget::mouseMoveEvent(event);
}

void Screen::resizeEvent(QResizeEvent *event)
{
    static QSize size;
    size = event->size();
    CUIMsgMgr::Send(Geometry::ScreenResize,&size,NULL);
    ui->label->setText(QString::number((double)width() / height()));
    QWidget::resizeEvent(event);
}
