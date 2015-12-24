#ifndef SWITCHABLELISTWIDGET_H
#define SWITCHABLELISTWIDGET_H

#include <QListWidget>

class QMouseEvent;
class QEvent;
class QListWidgetItem;

class SwitchableListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit SwitchableListWidget(QWidget *parent = 0);

    void AddItem(int num);
    void AddEmptyItem();

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void SwapItem(int src, int des);

private:
    QListWidgetItem* _dragItem;

};

#endif // SWITCHABLELISTWIDGET_H
