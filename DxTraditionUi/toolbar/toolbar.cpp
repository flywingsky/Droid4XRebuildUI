#include "toolbar.h"
#include "ui_toolbar.h"

#include "UIMsgMgr.h"
#include "msgdef.h"

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
        return qobject_cast<QPushButton*>(_buttons[name]);
    }
    return NULL;
}


void ToolBar::CreateButtons()
{
    _buttons["back"] = ui->pushButton;
    _buttons["home"] = ui->pushButton_2;
    _buttons["more"] = ui->pushButton_3;
    _buttons["blank"] = ui->spacerWidget;
    _buttons["full"] = new QPushButton(this);
    _buttons["shake"] = new QPushButton(this);
    _buttons["shot"] = new QPushButton(this);

    static QString vOrder[] = {"full", "shake", "shot", "blank", "back", "home", "more"};
    static QString hOrder[] = {"back", "home", "more","blank", "full", "shake", "shot"};

    for(int n=0; n<_buttons.size(); ++n)
    {
        _vLayout->append(CommonFunc::LayoutWidget(_buttons[vOrder[n]],QRect(n,0,1,1)));
        _hLayout->append(CommonFunc::LayoutWidget(_buttons[hOrder[n]],QRect(0,n,1,1)));

        QPushButton* btn = qobject_cast<QPushButton*>(_buttons.values()[n]);
        if(btn)
            connect(btn, SIGNAL(clicked()), this, SLOT(ButtonClicked()));

    }




}

void ToolBar::ButtonClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString key;
    if(btn)
        key = _buttons.key(btn);


    static QMap<QString, int> msg;
    if(msg.isEmpty())
    {
        msg["back"] = Btn::Back;
        msg["home"] = Btn::Home;
        msg["more"] = Btn::More;
        msg["full"] = Btn::Full;
        msg["shake"] = Btn::Shake;
        msg["shot"] = Btn::Shot;
    }

    CUIMsgMgr::Post(msg[key],NULL,NULL);

}

