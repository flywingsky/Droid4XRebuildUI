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
    static PageData *GetPageData(const QMimeData* d);


public:
    explicit SwitchableListWidget(QWidget *parent = 0);
    PageData *GetPageData(const ItemWidget* wnd);

    void AppendItem(PageData* d);


    QListWidgetItem * itemAtEx(const QPoint & p) const;

signals:
    void ActivePage(QWidget* w);
    void DragOut(QListWidgetItem* it);

public slots:
    void Test(Qt::DropAction action);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);


private:
    void JumpQueue(int src, int des, bool front = true);
    void ShowSnap(bool show);

    void HideItem(QListWidgetItem* it) const;
    void ShowItem(QListWidgetItem* it) const;

    void InitAnimation();
    void StartAnimation();

    QMimeData* CreateMimeData(QListWidgetItem* it) const;


private slots:
    void Active();


private:
    QListWidgetItem* _dragItem;
    QParallelAnimationGroup* _itemAnimation;
    QDrag* _drag;

};

#endif // SWITCHABLELISTWIDGET_H
