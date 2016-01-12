#include "switchablelistwidget.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>


#include "itemwidget.h"
#include <QDrag>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QMimeData>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include "pagedata.h"
#include "defprivate.h"
#include <QApplication>

SwitchableListWidget::SwitchableListWidget(QWidget *parent) :
    QListWidget(parent),
    _dragItem(NULL),
    _itemAnimation(NULL)
{
    setDragEnabled(true);
    setSpacing(1);
    setAcceptDrops(true);
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

PageData SwitchableListWidget::GetPageData(QListWidgetItem* it)
{
    return it->data(PAGE_DATA).value<PageData>();
}

ItemWidget *SwitchableListWidget::GetItemWidget(QListWidgetItem *it)
{
    return it->data(ITEM_WIDGET).value<ItemWidget*>();
}

QListWidgetItem *SwitchableListWidget::itemAtEx(const QPoint &p) const
{
    QListWidgetItem * it = itemAt(p);
    if(!it && count() > 0 && rect().contains(p))
    {
        if(p.y() > visualItemRect(item(count() - 1)).y())
            it = item(count() - 1);
        else if(p.y() < visualItemRect(item(0)).y())
            it = item(0);
    }
    return it;
}


void SwitchableListWidget::mousePressEvent(QMouseEvent * event)
{
    //_dragItem = itemAt(event->pos());
    QListWidget::mousePressEvent(event);
}

void SwitchableListWidget::mouseReleaseEvent(QMouseEvent * event)
{
    if(_dragItem)
    {
        ItemWidget* wnd = GetItemWidget(_dragItem);
        if(wnd->IsSnapHidden())
            wnd->setGeometry(visualItemRect(_dragItem));
        else
        {
            emit DragOut(_dragItem);
            ShowSnap(false);
            takeItem(row(_dragItem));
            qDebug() << count();
        }
    }
    _dragItem = NULL;
    qDebug() << "mouseReleaseEvent";
    QListWidget::mouseReleaseEvent(event);
}

void SwitchableListWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(_dragItem)
    {
        if(!rect().contains(event->pos()))
        {
            ShowSnap(true);
        }
        else
        {
            //qDebug() << "in";
            ShowSnap(false);

            QListWidgetItem* it = itemAtEx(event->pos());

            if(it)
            {
                if(it != _dragItem)
                {
                    InitAnimation();

                    QRect rc = itemWidget(_dragItem)->geometry();
                    JumpQueue(row(_dragItem), row(it), (row(_dragItem) > row(it)));
                    _dragItem = itemAtEx(event->pos());
                    itemWidget(_dragItem)->setGeometry(rc);

                    StartAnimation();

                }
            }
            ItemWidget* wnd = GetItemWidget(_dragItem);
            wnd->move(0,event->pos().y() - wnd->height() / 2);

        }

    }

    QListWidget::mouseMoveEvent(event);

}

void SwitchableListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dragEnterEvent";
    if (event->mimeData()->hasFormat(DRAG_FORMAT))
        event->accept();
    else
        event->ignore();
}

void SwitchableListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(DRAG_FORMAT))
    {
        ItemWidget* wnd = GetData(event->mimeData());
        QListWidgetItem* it = itemAtEx(event->pos());
        QListWidgetItem* dragIt = wnd->Item();

        if(it && it != dragIt)
        {
            QRect rc = itemWidget(dragIt)->geometry();
            JumpQueue(row(dragIt), row(it), (row(dragIt) > row(it)));
            dragIt = itemAtEx(event->pos());
            itemWidget(dragIt)->setGeometry(rc);
        }
        wnd->move(0,event->pos().y() - wnd->height() / 2);




        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();

}

void SwitchableListWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug() << "dragLeaveEvent";

    event->accept();
}

void SwitchableListWidget::dropEvent(QDropEvent *event)
{

    if (event->mimeData()->hasFormat(DRAG_FORMAT))
    {
        ItemWidget* wnd = GetData(event->mimeData());
        wnd->setGeometry(visualItemRect(wnd->Item()));


        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }

    qDebug() << "dropEvent";
}

void SwitchableListWidget::startDrag(Qt::DropActions supportedActions)
{
    qDebug() << "startDrag";

    ItemWidget* wnd = GetItemWidget(currentItem());
    QMimeData *mimeData = CreateMimeData(wnd);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint());

    drag->exec(Qt::MoveAction);
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


void SwitchableListWidget::ShowSnap(bool show)
{
    Q_ASSERT(_dragItem);
    ItemWidget* wnd = GetItemWidget(_dragItem);

    if(show)
    {
        if(wnd->IsSnapHidden())
        {
            PageData pdata = GetPageData(_dragItem);
            wnd->ShowSnap((QWidget*)pdata.page);
            wnd->hide();
            _dragItem->setSizeHint(QSize(0,0));
        }
    }
    else
    {
        if(!wnd->IsSnapHidden())
        {
            wnd->ShowSnap(NULL);
            _dragItem->setSizeHint(wnd->size());
            wnd->show();
            wnd->raise();
        }
    }
}

void SwitchableListWidget::InitAnimation()
{
    if(!_itemAnimation)
        _itemAnimation = new QParallelAnimationGroup;

    _itemAnimation->clear();

    for (int i = 0; i < count(); ++i)
    {
        QListWidgetItem* it = item(i);
        if(it == _dragItem)
            continue;

        QPropertyAnimation *anim = new QPropertyAnimation(GetItemWidget(it), "geometry", _itemAnimation);

        anim->setStartValue(visualItemRect(it));
        anim->setDuration(500 + i * 25);
        anim->setEasingCurve(QEasingCurve::Linear);

        _itemAnimation->addAnimation(anim);
    }
}

void SwitchableListWidget::StartAnimation()
{

    for(int n=0; n<_itemAnimation->animationCount(); ++n)
    {
        QPropertyAnimation* a = (QPropertyAnimation*)_itemAnimation->animationAt(n);
        ItemWidget* w = (ItemWidget*)a->targetObject();
        a->setEndValue(visualItemRect(((ItemWidget*)a->targetObject())->Item()));
    }

    _itemAnimation->start();
}

QMimeData *SwitchableListWidget::CreateMimeData(ItemWidget *wnd) const
{
    QByteArray dragData;
    QDataStream dataStream(&dragData, QIODevice::WriteOnly);
    dataStream << (int)wnd;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(DRAG_FORMAT, dragData);
    return mimeData;
}

ItemWidget *SwitchableListWidget::GetData(const QMimeData *d) const
{
    int tempWnd;

    QByteArray arr = d->data(DRAG_FORMAT);
    QDataStream dataStream(&arr, QIODevice::ReadOnly);
    dataStream >> tempWnd;

    return (ItemWidget*)tempWnd;
}


void SwitchableListWidget::Active()
{
    emit ActiveIndex(((ItemWidget*)sender())->Item()->data(PAGE_DATA).value<PageData>().index);
}

