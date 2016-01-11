#include "screen.h"
#include "ui_screen.h"

#include <QResizeEvent>

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

void Screen::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    ui->label->setText(QString::number((double)  event->size().width() / event->size().height()));
}
