#include "toolbar.h"
#include "ui_toolbar.h"

#include "UIMsgMgr.h"
#include "commonfunc.h"

#include <QPainter>

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
    CreateButtons();

}

ToolBar::~ToolBar()
{
    delete ui;
}

void ToolBar::SetLandscape()
{
    setMinimumSize(0,68);
    setMaximumSize(QWIDGETSIZE_MAX,68);
}

void ToolBar::SetPortrait()
{
    setMinimumSize(68,0);
    setMaximumSize(68,QWIDGETSIZE_MAX);
}


void ToolBar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter p(this);

    if(CommonFunc::IsLandscape(this))
        p.fillRect(QRect(0,0,width(),height()), QColor("#00ff00"));
    else
        p.fillRect(QRect(0,0,width(),height()), QColor("#00ffff"));
}

void ToolBar::resizeEvent(QResizeEvent *event)
{
    if(CommonFunc::IsLandscape(this))
        SetLandscape();
    else
        SetPortrait();
}


QPushButton *ToolBar::GetButton(QString name)
{
    if(_buttons.contains(name))
    {
        return _buttons[name];
    }
    return NULL;
}


void ToolBar::CreateButtons()
{
    _buttons["full"] = ui->pushButton;
    _buttons["set"] = ui->pushButton_2;
    _buttons["help"] = ui->pushButton_3;
}

