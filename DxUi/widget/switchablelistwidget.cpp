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
#include "page.h"

QDrag* SwitchableListWidget::_drag = NULL;

SwitchableListWidget::SwitchableListWidget(QWidget *parent) :
    QListWidget(parent),
    _dragItem(NULL),
    _itemAnimation(NULL)
{
    setDragEnabled(true);
    setAcceptDrops(true);
}

QListWidgetItem* SwitchableListWidget::AppendItem(PageData *d)
{
    QListWidgetItem* it = new QListWidgetItem(this);
    ItemWidget* wnd = new ItemWidget(this);

    wnd->SetText(d->title);

    it->setSizeHint(wnd->size());
    it->setData(PAGE_DATA, QVariant::fromValue(d));

    connect(wnd, SIGNAL(Pressed()), this, SLOT(Active()));

    addItem(it);
    setItemWidget(it, wnd);

    return it;
}

void SwitchableListWidget::DeleteItem(QListWidgetItem *it)
{
    disconnect(itemWidget(it), SIGNAL(Pressed()), this, SLOT(Active()));
    qDebug() << row(it);
    removeItemWidget(it);
    delete takeItem(row(it));
}


PageData* SwitchableListWidget::GetPageData(const QListWidgetItem* it)
{
    return it->data(PAGE_DATA).value<PageData*>();
}


PageData *SwitchableListWidget::GetPageData(const ItemWidget *wnd)
{
    for(int n=0; n<count(); ++n)
    {
        if(wnd == itemWidget(item(n)))
            return GetPageData(item(n));
    }

    return NULL;
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


void SwitchableListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dragEnterEvent";
    if (event->mimeData()->hasFormat(DRAG_FORMAT))
    {
        PageData* d = ReadMimeData(event->mimeData());
        emit DragEnter(d);
        if(!_dragItem)
            _dragItem = AppendItem(d);
        QWidget* wnd = itemWidget(_dragItem);
        wnd->move(0,event->pos().y() - wnd->height() / 2);


        event->accept();
    }
    else
        event->ignore();
}

void SwitchableListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(DRAG_FORMAT) && _dragItem)
    {
        ItemWidget* wnd = (ItemWidget*)itemWidget(_dragItem);
        QListWidgetItem* it = itemAtEx(event->pos());

        if(it && it != _dragItem)
            JumpQueue(row(_dragItem), row(it));

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
    if(_drag && _dragItem)
    {
        PageData* d = ReadMimeData(_drag->mimeData());
        emit DragLeave(d);
        _drag->setPixmap(d->page->grab());

        DeleteItem(_dragItem);
        _dragItem = NULL;
    }

    event->accept();
}

void SwitchableListWidget::dropEvent(QDropEvent *event)
{

    if (event->mimeData()->hasFormat(DRAG_FORMAT))
    {
        // item已经在列表内，直接调整窗口位置
        itemWidget(_dragItem)->setGeometry(visualItemRect(_dragItem));
        _dragItem = NULL;


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
    _drag = new QDrag(this);
    _dragItem = currentItem();
    PageData* d = GetPageData(currentItem());
    _drag->setMimeData(CreateMimeData(d));
    _drag->setHotSpot(QPoint());
    if(_drag->exec(Qt::MoveAction) == Qt::IgnoreAction)
    {
        emit DragOut(d);
    }
    qDebug() << "endDrag";
}




void SwitchableListWidget::JumpQueue(int src, int des)
{
    Q_ASSERT(des >=0 && des < count());
    Q_ASSERT(src >=0 && src < count());

    if(src == des)
        return;

    // 放入站位item
    QListWidgetItem* it = item(src);

    QListWidgetItem* itTemp = it->clone();

    // 缓存
    addItem(itTemp);
    setItemWidget(itTemp,itemWidget(it));

    // 交换位置
    insertItem(des, takeItem(row(it)));
    setItemWidget(it, itemWidget(itTemp));

    delete takeItem(row(itTemp));

}



void SwitchableListWidget::HideItem(QListWidgetItem *it) const
{
    QWidget* wnd = itemWidget(it);
    wnd->hide();
    it->setSizeHint(QSize(0,0));
}

void SwitchableListWidget::ShowItem(QListWidgetItem *it) const
{
    QWidget* wnd = itemWidget(it);
    it->setSizeHint(wnd->size());
    wnd->show();
    wnd->raise();

}

void SwitchableListWidget::InitAnimation()
{
//    if(!_itemAnimation)
//        _itemAnimation = new QParallelAnimationGroup;

//    _itemAnimation->clear();

//    for (int i = 0; i < count(); ++i)
//    {
//        QListWidgetItem* it = item(i);
//        if(it == _dragItem)
//            continue;

//        QPropertyAnimation *anim = new QPropertyAnimation(GetItemWidget(it), "geometry", _itemAnimation);

//        anim->setStartValue(visualItemRect(it));
//        anim->setDuration(500 + i * 25);
//        anim->setEasingCurve(QEasingCurve::Linear);

//        _itemAnimation->addAnimation(anim);
//    }
}

void SwitchableListWidget::StartAnimation()
{

//    for(int n=0; n<_itemAnimation->animationCount(); ++n)
//    {
//        QPropertyAnimation* a = (QPropertyAnimation*)_itemAnimation->animationAt(n);
//        ItemWidget* w = (ItemWidget*)a->targetObject();
//        a->setEndValue(visualItemRect(((ItemWidget*)a->targetObject())->Item()));
//    }

//    _itemAnimation->start();
}

QMimeData *SwitchableListWidget::CreateMimeData(PageData* d)
{
    QByteArray dragData;
    QDataStream dataStream(&dragData, QIODevice::WriteOnly);
    dataStream << (int)(d);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(DRAG_FORMAT, dragData);
    return mimeData;
}



PageData* SwitchableListWidget::ReadMimeData(const QMimeData *d)
{
    int tempWnd;

    QByteArray arr = d->data(DRAG_FORMAT);
    QDataStream dataStream(&arr, QIODevice::ReadOnly);
    dataStream >> tempWnd;

    return (PageData*)tempWnd;
}



void SwitchableListWidget::Active()
{
    PageData* d = GetPageData((ItemWidget*)sender());
    emit ActivePage(d->page);
}

