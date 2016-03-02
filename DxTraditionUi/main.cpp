#include <QApplication>

#include "mainpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainPanel p;
    p.show();

    return a.exec();
}
