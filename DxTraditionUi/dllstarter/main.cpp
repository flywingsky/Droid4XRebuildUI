#include <QApplication>

#include "ui_ship.h"
#include "ui_nothing.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    ui_nothing* un = new ui_nothing();
    un->Run();

//    ui_ship* us = new ui_ship();
//    us->Run();


    return a.exec();
}
