#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ItemWidget;
}
class FramelessMove;
class SnapshotPage;

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = 0);
    ~ItemWidget();

    void SetText(QString t);
    QString Text() const;

signals:
    void Pressed();

protected:

private:
    Ui::ItemWidget *ui;
    FramelessMove* _frame;
};

#endif // ITEMWIDGET_H
