#ifndef SWITCHABLELISTWIDGET_H
#define SWITCHABLELISTWIDGET_H

#include <QListWidget>

class QMouseEvent;
class QEvent;
class QListWidgetItem;
class PageData;
class ItemWidget;
class QParallelAnimationGroup;

class SwitchableListWidget : public QListWidget
{
    Q_OBJECT
public:
    static PageData *GetPageData(const QListWidgetItem* it);

    static PageData *ReadMimeData(const QMimeData* d);
    static QMimeData* CreateMimeData(PageData *d);


public:
    explicit SwitchableListWidget(QWidget *parent = 0);
    PageData *GetPageData(const ItemWidget* wnd);

    QListWidgetItem *AppendItem(PageData* d);
    void DeleteItem(QListWidgetItem* it);


    QListWidgetItem * itemAtEx(const QPoint & p) const;

signals:
    void ActivePage(QWidget* w);
    void DragLeave(PageData* d);
    void DragEnter(PageData* d);
    void DragOut(PageData* d);

public slots:

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);


private:
    void JumpQueue(int src, int des);

    void HideItem(QListWidgetItem* it) const;
    void ShowItem(QListWidgetItem* it) const;

    void InitAnimation();
    void StartAnimation();




private slots:
    void Active();


private:
    QListWidgetItem* _dragItem;
    QParallelAnimationGroup* _itemAnimation;
    static QDrag* _drag;


};

#endif // SWITCHABLELISTWIDGET_H
