#include "toolbar.h"
#include "ui_toolbar.h"

#include <QListWidgetItem>

Toolbar::Toolbar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Toolbar)
{
    ui->setupUi(this);

    for(int n=0; n<20; ++n)
    {
        ui->listWidget->addItem(QString::number(n));
        ui->listWidget->item(n)->setSizeHint(QSize(50,50));
    }
}

Toolbar::~Toolbar()
{
    delete ui;
}
