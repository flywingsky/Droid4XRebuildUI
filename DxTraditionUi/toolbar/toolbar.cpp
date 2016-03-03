#include "toolbar.h"
#include "ui_toolbar.h"

#include "UIMsgMgr.h"

ToolBar::ToolBar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(testPost()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(testSend()));

}

ToolBar::~ToolBar()
{
    delete ui;
}

void ToolBar::testPost()
{
    IMsgMgr* mgr = CUIMsgMgr::GetMsgMgr();
    QString* msg = new QString("this is test post");
    mgr->PostMsg(112,msg,NULL);
}

void ToolBar::testSend()
{
    IMsgMgr* mgr = CUIMsgMgr::GetMsgMgr();
    QString msg("this is test send");
    mgr->SendMsg(221,NULL,&msg);
}
