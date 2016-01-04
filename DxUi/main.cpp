#include "mainpanel.h"
#include <QApplication>


#include "dxui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DxUi* ui = new DxUi(&a);

    return a.exec();
}
