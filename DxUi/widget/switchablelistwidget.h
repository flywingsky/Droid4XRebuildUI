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
    static PageData GetPageData(QListWidgetItem* it);
    static ItemWidget* GetItemWidget(QListWidgetItem* it);

public:
    explicit SwitchableListWidget(QWidget *parent = 0);

    void AppendItem(const PageData& d);


    QListWidgetItem * itemAtEx(const QPoint & p) const;

signals:
    void ActiveIndex(int i);
    void DragOut(QListWidgetItem* it);

public slots:
    void Text();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    void JumpQueue(int src, int des, bool front = true);
    void ShowSnap(bool show);

    void InitAnimation();
    void StartAnimation();

private slots:
    void Active();


private:
    QListWidgetItem* _dragItem;
    QParallelAnimationGroup* _itemAnimation;

};

#endif // SWITCHABLELISTWIDGET_H
