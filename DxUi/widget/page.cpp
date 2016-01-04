#include "page.h"
#include "ui_page.h"

Page::Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page)
{
    ui->setupUi(this);
}

Page::~Page()
{
    delete ui;
}

Title *Page::TitleWidget()
{
    return ui->title;
}

Screen *Page::ScreenWidget()
{
    return ui->screen;
}
