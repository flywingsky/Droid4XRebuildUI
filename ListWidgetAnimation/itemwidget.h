#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ItemWidget;
}

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = 0);
    ~ItemWidget();
    void SetNum(int num);

protected:
    bool eventFilter(QObject *obj, QEvent *ev);
private:
    Ui::ItemWidget *ui;
};

#endif // ITEMWIDGET_H
