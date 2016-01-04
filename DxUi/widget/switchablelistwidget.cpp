#include "switchablelistwidget.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>


#include "itemwidget.h"
#include <QLineEdit>
#include <QListWidgetItem>
#include "pagedata.h"
#include "defprivate.h"

SwitchableListWidget::SwitchableListWidget(QWidget *parent) :
    QListWidget(parent),
    _dragItem(NULL)
{
}

void SwitchableListWidget::AppendItem(const PageData &d)
{
    QListWidgetItem* it = new QListWidgetItem(this);
    ItemWidget* wnd = new ItemWidget(this);

    wnd->SaveItem(it);
    wnd->SetText(d.title);

    it->setSizeHint(wnd->size());
    it->setData(PAGE_DATA, QVariant::fromValue(d));
    it->setData(ITEM_WIDGET, QVariant::fromValue(wnd));

    connect(wnd, SIGNAL(Pressed()), this, SLOT(Active()));


    addItem(it);
    setItemWidget(it, wnd);
}


void SwitchableListWidget::mousePressEvent(QMouseEvent * event)
{
    _dragItem = itemAt(event->pos());
    QListWidget::mousePressEvent(event);
}

void SwitchableListWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if(_dragItem)
    {
        QWidget* wnd = itemWidget(_dragItem);
        if(wnd)
            wnd->setGeometry(visualItemRect(_dragItem));
    }
    _dragItem = NULL;
    QListWidget::mouseReleaseEvent(event);
}

void SwitchableListWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(_dragItem)
    {
        QListWidgetItem* it = itemAt(event->pos());
        if(it)
        {
            if(it != _dragItem)
            {
                QRect rc = itemWidget(_dragItem)->geometry();
                JumpQueue(row(_dragItem), row(it), (row(_dragItem) > row(it)));
                _dragItem = itemAt(event->pos());
                itemWidget(_dragItem)->setGeometry(rc);
            }
        }
    }

    QListWidget::mouseMoveEvent(event);

}




void SwitchableListWidget::JumpQueue(int src, int des, bool front)
{
    Q_ASSERT(des >=0 && des < count());
    Q_ASSERT(src >=0 && src < count());

    if(src == des)
        return;

    // 放入站位item
    QListWidgetItem* it = item(src);
    QListWidgetItem* itNew = new QListWidgetItem(*it);
    insertItem(des + (front ? 0 : 1), itNew);
    ItemWidget* wnd = itNew->data(ITEM_WIDGET).value<ItemWidget*>();
    wnd->SaveItem(itNew);
    setItemWidget(itNew, wnd);

    delete takeItem(row(it));

}


void SwitchableListWidget::Active()
{
    qDebug() << ((ItemWidget*)sender())->Item()->data(PAGE_DATA).value<PageData>().index;
    emit ActiveIndex(((ItemWidget*)sender())->Item()->data(PAGE_DATA).value<PageData>().index);
}

