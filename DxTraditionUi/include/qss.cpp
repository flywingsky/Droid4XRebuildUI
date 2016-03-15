#include "qss.h"

#include <QFile>
#include <QWidget>

QFile* qssfiles[] = {
    new QFile("://qss/QListWidget.qss"),
    new QFile("://qss/QLineEdit.qss"),
    new QFile(":/qss/qss/ScrollBar.qss"),
    new QFile("://qpushbutton.qss"),
    new QFile(":/qss/qss/QDialog.qss"),
    new QFile(":/qss/QLabel.qss"),
    new QFile(":/qss/QMenu.qss"),
    new QFile("://title.qss")

};

Qss::Qss(QObject *parent) :
    QObject(parent)
{
    _p = (QWidget*)parent;
}

void Qss::AddSheet(int type, bool cover)
{
    if(cover)
        _sheet = _p->styleSheet();
    _sheet += StyleSheet(type);
}

void Qss::Sync()
{
    _p->setStyleSheet(_sheet);
}

QString Qss::StyleSheet(int type) const
{
    qssfiles[type]->open(QIODevice::ReadOnly);
    QString ss = qssfiles[type]->readAll();
    qssfiles[type]->close();
    return ss;
}
