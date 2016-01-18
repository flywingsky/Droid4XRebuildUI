#ifndef PAGEDATA_H
#define PAGEDATA_H

#include <QObject>
class Page;
class QListWidgetItem;
class ItemWidget;
class MainPanel;
class SwitchableListWidget;

class PageData : public QObject
{
    Q_OBJECT
public:
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
