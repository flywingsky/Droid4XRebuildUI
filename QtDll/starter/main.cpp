#include <QApplication>

#include "../QtExport/qtexport_global.h"
#include "../QtExport/qtexport.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << new QtExport();


    return a.exec();
}

