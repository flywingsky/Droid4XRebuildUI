#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ItemWidget;
}
class FramelessMove;
class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = 0);
    ~ItemWidget();
    void SetNum(int num);

protected:
    //bool eventFilter(QObject *obj, QEvent *ev);

private slots:
    void Move(QPoint pt);
private:
    Ui::ItemWidget *ui;
    FramelessMove* _frame;
};

#endif // ITEMWIDGET_H
