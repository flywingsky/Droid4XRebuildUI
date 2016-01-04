#ifndef SWITCHABLELISTWIDGET_H
#define SWITCHABLELISTWIDGET_H

#include <QListWidget>

class QMouseEvent;
class QEvent;
class QListWidgetItem;
class PageData;

class SwitchableListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit SwitchableListWidget(QWidget *parent = 0);

    void AppendItem(const PageData& d);

signals:
    void ActiveIndex(int i);

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    void JumpQueue(int src, int des, bool front = true);

private slots:
    void Active();


private:
    QListWidgetItem* _dragItem;

};

#endif // SWITCHABLELISTWIDGET_H
