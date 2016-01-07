#include "snapshotpage.h"
#include "ui_snapshotpage.h"

#include <QPainter>
#include <QDebug>
#include "framelessmove.h"

#include <QApplication>

SnapshotPage::SnapshotPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SnapshotPage),
    _snapshot(NULL)
{
    ui->setupUi(this);
    FramelessMove::SetFrameLess(true, this);
    setMouseTracking(true);
    qApp->installEventFilter(this);
}

SnapshotPage::~SnapshotPage()
{
    delete ui;
}

void SnapshotPage::SetWidget(QWidget *p)
{
    if(_snapshot)
        delete _snapshot;

    if(p)
        _snapshot = new QPixmap(p->grab());
    else
        _snapshot = NULL;

    update();
}

void SnapshotPage::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);

    QPainter p(this);
    if(_snapshot)
        p.drawPixmap(rect(), *_snapshot);
}
