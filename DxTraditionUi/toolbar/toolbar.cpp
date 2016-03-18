#include "toolbar.h"
#include "ui_toolbar.h"

#include "UIMsgMgr.h"

#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar),
    _hLayout(new CommonFunc::LayoutItems),
    _vLayout(new CommonFunc::LayoutItems)
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

    QGridLayout* l = (QGridLayout*)layout();
    CommonFunc::Relayout(*_hLayout,l);

}

void ToolBar::SetPortrait()
{
    setMinimumSize(68,0);
    setMaximumSize(68,QWIDGETSIZE_MAX);


    QGridLayout* l = (QGridLayout*)layout();
    CommonFunc::Relayout(*_vLayout,l);

}


void ToolBar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter p(this);

    if(CommonFunc::IsLandscape(this))
    {
        QPixmap pic("://toobar_bk.jpg");
        p.drawPixmap(QRect(0,0,200,height()), pic, QRect(0,0,1,pic.height()));
        p.drawPixmap(QRect(200,0,60,height()), pic, QRect(205,0,60,pic.height()));
        p.drawPixmap(QRect(260,0,width(),height()), pic, QRect(pic.width()-1,0,1,pic.height()));
    }
    else
    {
        p.fillRect(QRect(0,0,width(),height()), QColor("#e1e1e1"));
    }
}

void ToolBar::resizeEvent(QResizeEvent *event)
{
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
    _buttons["back"] = ui->pushButton;
    _buttons["home"] = ui->pushButton_2;
    _buttons["more"] = ui->pushButton_3;
    _buttons["full"] = new QPushButton;

    _vLayout->append(CommonFunc::LayoutWidget(_buttons["full"],QRect(0,0,1,1)));
    _vLayout->append(CommonFunc::LayoutWidget(ui->spacerWidget,QRect(1,0,1,1)));
    _vLayout->append(CommonFunc::LayoutWidget(_buttons["back"],QRect(2,0,1,1)));
    _vLayout->append(CommonFunc::LayoutWidget(_buttons["home"],QRect(3,0,1,1)));
    _vLayout->append(CommonFunc::LayoutWidget(_buttons["more"],QRect(4,0,1,1)));

    _hLayout->append(CommonFunc::LayoutWidget(_buttons["back"],QRect(0,0,1,1)));
    _hLayout->append(CommonFunc::LayoutWidget(_buttons["home"],QRect(0,1,1,1)));
    _hLayout->append(CommonFunc::LayoutWidget(_buttons["more"],QRect(0,2,1,1)));
    _hLayout->append(CommonFunc::LayoutWidget(ui->spacerWidget,QRect(0,3,1,1)));
    _hLayout->append(CommonFunc::LayoutWidget(_buttons["full"],QRect(0,4,1,1)));



}

