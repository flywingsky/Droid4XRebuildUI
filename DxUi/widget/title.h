#ifndef TITLE_H
#define TITLE_H

#include <QWidget>

namespace Ui {
class Title;
}

class FramelessMove;
class MainPanel;




class Title : public QWidget
{
    Q_OBJECT

public:
    explicit Title(QWidget *parent = 0);
    ~Title();

    bool MaxWindow();

    void SetMoveTarget(QWidget* w);

    void SetText(const QString& text);

    void SetMainPanel(MainPanel * p);



signals:
    void MinWnd();
    void MaxWnd();
    void NormalWnd();
    void CloseWnd();


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
    FramelessMove* _frame;
    MainPanel * _panel;
};

#endif // TITLE_H
