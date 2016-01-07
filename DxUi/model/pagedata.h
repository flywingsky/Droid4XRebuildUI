#ifndef PAGEDATA_H
#define PAGEDATA_H

#include <QObject>
class Page;

class PageData : public QObject
{
    Q_OBJECT
public:
    int index;
    QString title;
    Page* page;

public:
    explicit PageData(QObject *parent = 0);
    PageData(const PageData& other);

signals:

public slots:
};

Q_DECLARE_METATYPE(PageData)

#endif // PAGEDATA_H
