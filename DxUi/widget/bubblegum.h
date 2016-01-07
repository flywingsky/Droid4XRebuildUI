#ifndef BUBBLEGUM_H
#define BUBBLEGUM_H

#include <QPushButton>

namespace Ui {
class BubbleGum;
}

class FramelessMove;

class BubbleGum : public QPushButton
{
    Q_OBJECT

public:
    explicit BubbleGum(QWidget *parent = 0);
    ~BubbleGum();

protected:
    virtual void	paintEvent(QPaintEvent * event);

private slots:
    void DragMove(QPoint pos);
    void Pressed(QPoint pos);
    void Released(QPoint pos);

private:
    Ui::BubbleGum *ui;
    FramelessMove* _fm;
    qreal _radius;
    QPoint _dragPos;
};

#endif // BUBBLEGUM_H
