#ifndef SCREENFRAME_H
#define SCREENFRAME_H

#include <QWidget>

namespace Ui {
class ScreenFrame;
}

class Screen;

class ScreenFrame : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenFrame(QWidget *parent = 0);
    ~ScreenFrame();

    Screen* GetScreen() const;

    QSize GetScale() const;
    void SetScale(QSize s);

protected:
    virtual void	resizeEvent(QResizeEvent * event);

private slots:
    void RescaleScreen();


private:
    Ui::ScreenFrame *ui;
    QSize _scale;
};

#endif // SCREENFRAME_H
