#include "screenframe.h"
#include "ui_screenframe.h"

ScreenFrame::ScreenFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenFrame)
{
    ui->setupUi(this);
}

ScreenFrame::~ScreenFrame()
{
    delete ui;
}

Screen *ScreenFrame::GetScreen() const
{
    return ui->screen;
}

QSize ScreenFrame::GetScale() const
{
    return _scale;
}

void ScreenFrame::SetScale(QSize s)
{
    if(_scale != s)
    {
        _scale = s;
        RescaleScreen();
    }
}

void ScreenFrame::resizeEvent(QResizeEvent *event)
{
    RescaleScreen();
}

void ScreenFrame::RescaleScreen()
{
    if(_scale.isValid() && !_scale.isEmpty())
    {
        ui->screen->resize(_scale.scaled(size(),Qt::KeepAspectRatio));
        QSize temp = (size() - ui->screen->size()) / 2;
        ui->screen->move(temp.width(), temp.height());
    }
    else
    {
        ui->screen->resize(size());
        ui->screen->move(0,0);
    }
}
