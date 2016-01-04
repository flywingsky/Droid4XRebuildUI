#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ItemWidget;
}
class FramelessMove;
class QListWidgetItem;

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = 0);
    ~ItemWidget();
    void SetText(QString t);
    void SaveItem(QListWidgetItem* it);
    QListWidgetItem* Item();

signals:
    void Pressed();

protected:

private slots:
    void Move(QPoint pt);
private:
    Ui::ItemWidget *ui;
    FramelessMove* _frame;
    QListWidgetItem* _it;
};

#endif // ITEMWIDGET_H
