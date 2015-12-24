#ifndef TITLE_H
#define TITLE_H

#include <QWidget>

namespace Ui {
class Title;
}

class Title : public QWidget
{
    Q_OBJECT

public:
    Q_PROPERTY(bool MaxWindow READ MaxWindow WRITE setMaxWindow NOTIFY MaxWindowChanged)
public:
    explicit Title(QWidget *parent = 0);
    ~Title();

    bool MaxWindow();



signals:
    void MinWnd();
    void MaxWnd();
    void NormalWnd();
    void CloseWnd();

    void MaxWindowChanged(bool max);

public slots:
    void setMaxWindow(bool max);


protected:
    virtual void mouseDoubleClickEvent(QMouseEvent * event);
    bool eventFilter(QObject *obj, QEvent *ev);


private slots:
    void ReverseMaxStatus();
    bool DragTitle();

private:
    Ui::Title *ui;
    bool _maxWindow;
};

#endif // TITLE_H
