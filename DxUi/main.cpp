#include "mainpanel.h"
#include <QApplication>


#include "dxui.h"
#include "pagedata.h"
#include "page.h"
#include "screen.h"

#include "toolbar.h"
#include "bubblegum.h"


QWidget* CreateWnd(QString name);       // 测试用接口

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 测试创建3个
    for(int n=0; n<3; ++n)
    {
        CreateWnd(QString("the number ") + QString::number(n));
    }



//    Toolbar* t = new Toolbar();
//    t->show();

//    BubbleGum* b = new BubbleGum();
//    b->show();

    return a.exec();
}



QWidget* CreateWnd(QString name)
{
    static DxUi* ui = NULL;
    if(!ui)
        ui = new DxUi();

    PageData* d = new PageData;
    d->title = name;

    MainPanel* p = ui->CreatePanel();
    ui->AddPage(p,d);

    p->show();

    return d->page->ScreenWidget();
}
