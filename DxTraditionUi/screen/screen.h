#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>

namespace Ui {
class Screen;
}

class Screen : public QWidget
{
    Q_OBJECT

public:
    explicit Screen(QWidget *parent = 0);
    ~Screen();

protected:
    virtual void	mousePressEvent(QMouseEvent * event);
    virtual void	mouseReleaseEvent(QMouseEvent * event);
    virtual void	mouseMoveEvent(QMouseEvent * event);
    virtual void	resizeEvent(QResizeEvent * event);

private:
    Ui::Screen *ui;
};

#endif // SCREEN_H
