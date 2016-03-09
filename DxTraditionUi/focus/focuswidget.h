#ifndef FOCUSWIDGET_H
#define FOCUSWIDGET_H

#include <QWidget>

/*!
 * @class FocusWidget 为实现输入法窗口跟随光标，隐藏的焦点控件
 */
class FocusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FocusWidget(QWidget *parent = 0);
     ~FocusWidget();

protected:
    virtual void	inputMethodEvent(QInputMethodEvent * event);

    virtual void	paintEvent(QPaintEvent * event);
    virtual void	keyPressEvent(QKeyEvent * event);

signals:

public slots:

private:
    void ShakeWidget();

};

#endif // FOCUSWIDGET_H
