#include "qtexport.h"

#include <QDebug>

#include <QDialog>

QtExport::QtExport()
{
    QDialog* d = new QDialog();
    d->show();
}
