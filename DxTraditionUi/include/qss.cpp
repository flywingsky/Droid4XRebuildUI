#include "qss.h"

#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <QDebug>

QString qssfiles[] = {
    "://qss/QListWidget.qss",
    "://qss/QLineEdit.qss",
    ":/qss/qss/ScrollBar.qss",
    "://qpushbutton.qss",
    ":/qss/qss/QDialog.qss",
    ":/qss/QLabel.qss",
    ":/qss/QMenu.qss",
    "://title.qss"

};

QString Qss::StyleSheet(int type)
{
    QFile f(qssfiles[type]);
    f.open(QIODevice::ReadOnly|QIODevice::Text);

    QString ss = f.readAll();

    f.close();
    return ss;
}

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
