#include "dialog.h"
#include "ui_dialog.h"


#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->listWidget->setSpacing(2);
    for (int n = 0; n< 5; ++n)
    {
        ui->listWidget->AddItem(n);

    }
}

Dialog::~Dialog()
{
    delete ui;
}
