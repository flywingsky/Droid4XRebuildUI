#include "switchablelistwidget.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>


#include "itemwidget.h"
#include <QListWidgetItem>

SwitchableListWidget::SwitchableListWidget(QWidget *parent) :
    QListWidget(parent),
    _dragItem(NULL)
{
}

void SwitchableListWidget::AddItem(int num)
{
    QListWidgetItem* it = new QListWidgetItem(this);
    ItemWidget* wnd = new ItemWidget(this);
    it->setSizeHint(wnd->size());
    wnd->SetNum(num);

    setItemWidget(it, wnd);

}

void SwitchableListWidget::AddEmptyItem()
{
    QListWidgetItem* it = new QListWidgetItem(this);
    ItemWidget wnd(this);
    it->setSizeHint(wnd.size());


    addItem(it);
}


void SwitchableListWidget::mousePressEvent(QMouseEvent * event)
{
    _dragItem = itemAt(event->pos());

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
                SwapItem(row(_dragItem), row(it));
                _dragItem = itemAt(event->pos());
                itemWidget(_dragItem)->setGeometry(rc);
            }
        }
        else
        {

        }
    }

}



void SwitchableListWidget::SwapItem(int src, int des)
{
    if( src < 0 || src >= count() ||
        des < 0 || des >= count() ||
        des == src)
        return;

    int nFront = qMin(src,des);
    int nLatter = qMax(src,des);

    // 成功交换 界面修改
    insertItem(nLatter,"");        // 先插入后面的Item 前面的Item位置不受影响
    insertItem(nFront,"");

    QListWidgetItem*  pFrontItem= item(nFront);
    QListWidgetItem*  pLatterItem= item(nLatter + 1);    // 因为前面多插入了一个nFront 所以 +1


    pFrontItem->setSizeHint(visualItemRect(item(nFront + 1)).size());    // 设定大小
    pLatterItem->setSizeHint(visualItemRect(item(nLatter + 2)).size());    // 设定大小

    // 获得之前设定的窗口
    QWidget* pFrontCell = itemWidget(item(nFront + 1));
    QWidget* pLatterCell = itemWidget(item(nLatter + 2));

    if(pFrontCell)
        setItemWidget(pLatterItem, pFrontCell);

    if(pLatterCell)
        setItemWidget(pFrontItem, pLatterCell);

    delete takeItem(nLatter+2);
    delete takeItem(nFront+1);

}

