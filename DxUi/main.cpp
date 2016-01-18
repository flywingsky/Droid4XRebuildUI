#include "mainpanel.h"
#include <QApplication>


#include "dxui.h"

#include "toolbar.h"
#include "bubblegum.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DxUi* ui = new DxUi(&a);
//    Toolbar* t = new Toolbar();
//    t->show();

//    BubbleGum* b = new BubbleGum();
//    b->show();

    return a.exec();
}
