#include "page.h"
#include "panel.h"

Panel::Panel(QWidget *parent) : QStackedWidget(parent)
{

}

void Panel::AddPage()
{

}

Page *Panel::CurrentPage()
{
    return (Page*)currentWidget();
}

