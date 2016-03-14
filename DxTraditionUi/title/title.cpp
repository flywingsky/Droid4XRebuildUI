#include "title.h"
#include "ui_title.h"

#include <QPainter>

#include "qss.h"

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title)
{
    ui->setupUi(this);

    CreateButtons();

    Qss* qss = new Qss(this);
    qss->AddSheet(Qss::Title);
    qss->Sync();

}

Title::~Title()
{
    delete ui;
}

QPushButton *Title::GetButton(QString name)
{
    if(_buttons.contains(name))
    {
        return _buttons[name];
    }
    return NULL;
}


void Title::CreateButtons()
{
    _buttons["close"] = ui->btnClose;
    _buttons["max"] = ui->btnMax;
    _buttons["min"] = ui->btnMin;
    _buttons["at"] = ui->pushButton;
    _buttons["set"] = ui->pushButton_2;
    _buttons["help"] = ui->pushButton_3;
}

void Title::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit DoubleClicked();
    QWidget::mouseDoubleClickEvent(event);
}

void Title::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

