#include "title.h"
#include "ui_title.h"

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title)
{
    ui->setupUi(this);

    CreateButtons();
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
}

void Title::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit DoubleClicked();
    QWidget::mouseDoubleClickEvent(event);
}



