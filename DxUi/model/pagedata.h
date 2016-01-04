#ifndef PAGEDATA_H
#define PAGEDATA_H

#include <QObject>

class PageData : public QObject
{
    Q_OBJECT
public:
    int index;
    QString title;

public:
    explicit PageData(QObject *parent = 0);
    PageData(const PageData& other);

signals:

public slots:
};

Q_DECLARE_METATYPE(PageData)

#endif // PAGEDATA_H
