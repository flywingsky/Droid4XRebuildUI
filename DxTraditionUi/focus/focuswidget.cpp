#include "focuswidget.h"
#include <QInputMethodEvent>
#include <QTextCodec>
#include <QKeyEvent>
#include <QApplication>
#include "IMsgObsever.h"
#include "UIMsgMgr.h"
#include "msgdef.h"


#include <QDebug>

#ifdef WIN32
#include <QPainter>
#include <QPushButton>
#include <qt_windows.h>
#endif


FocusWidget::FocusWidget(QWidget *parent) :
    QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled, true);
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(FocusChanged(QWidget*,QWidget*)));
}

FocusWidget::~FocusWidget()
{
}

void FocusWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter p(this);
    // 设置焦点窗口为透明，没必要显示
    p.fillRect(0,0,width(),height(),QColor("#00ffff00"));

}

void FocusWidget::keyPressEvent(QKeyEvent *event)
{
    IMsgMgr* msg = CUIMsgMgr::GetMsgMgr();
    static long vk;
    vk = event->nativeVirtualKey();
    qDebug() << "keyPressEvent" << vk;

    msg->PostMsg(InOut::KeyDown, &vk,event);
}


void FocusWidget::ShakeWidget()
{
    static uint flag = 0;
    flag = (flag + 1) % 2;
    QPoint pt = this->pos();
    pt.setX(pt.x() + (flag?1:-1));
    move(pt);
}

void FocusWidget::FocusChanged(QWidget *old, QWidget *now)
{
    if(qobject_cast<QPushButton*>(now))
        setFocus();
}

void FocusWidget::inputMethodEvent(QInputMethodEvent *event)
{
    // 窗体如果不晃动，输入法的位置，就不是窗口位置
    ShakeWidget();


    QString inputString = event->commitString();
    if(inputString.length() == 0)
    {
        event->accept();
        return;
    }
    IMsgMgr* msg = CUIMsgMgr::GetMsgMgr();
    static QString stringBuff;
    stringBuff = inputString;
    msg->PostMsg(InOut::StringInput, &stringBuff,NULL);

    event->accept();
}

