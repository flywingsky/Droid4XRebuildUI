#include <QApplication>


#include "dxui.h"
#include "IMsgObsever.h"

#pragma comment(lib, "dllpro.lib")




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DxUi* ui = new DxUi();
    ui->CreateMainWnd();

    return a.exec();
}
