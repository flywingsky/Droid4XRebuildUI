#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

namespace Ui {
class ToolBar;
}

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = 0);
    ~ToolBar();

    void SetLandscape();
    void SetPortrait();

protected:
    virtual void	paintEvent(QPaintEvent * event);
    virtual void	resizeEvent(QResizeEvent * event);


private slots:



private:
    Ui::ToolBar *ui;
};

#endif // TOOLBAR_H
