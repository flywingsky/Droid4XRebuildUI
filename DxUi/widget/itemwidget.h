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
    void ShowSnap(QWidget *snapWidget);
    bool IsSnapHidden();

signals:
    void Pressed();
    void Offset(QPoint pt);

protected:

private slots:
    void Move(QPoint pt);
private:
    Ui::ItemWidget *ui;
    FramelessMove* _frame;
    SnapshotPage* _snappage;
};

#endif // ITEMWIDGET_H
