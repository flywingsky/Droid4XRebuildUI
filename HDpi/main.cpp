#include "dialog.h"
#include <QApplication>
#include <QDebug>
#include <QScreen>

#include "dpitransform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    DpiTransform::Transform();

    return a.exec();
}
