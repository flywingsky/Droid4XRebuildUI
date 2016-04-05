#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QMap>
#include "commonfunc.h"

namespace Ui {
class ToolBar;
}

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QSpacerItem;
class FloatAnimation;

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = 0);
    ~ToolBar();

    void SetLandscape();
    void SetPortrait();

    // 设置自动的浮动，在给定的父窗口范围。
    void SetAutoFloat(QWidget *parent);
    void StopAutoFloat();

    QPushButton *GetButton(QString name);
protected:
    virtual void	paintEvent(QPaintEvent * event);
    virtual void	resizeEvent(QResizeEvent * event);

private:
    void CreateButtons();


private slots:
    void ButtonClicked();



private:
    Ui::ToolBar *ui;
    QMap<QString, QWidget*> _buttons;
    CommonFunc::LayoutItems* _hLayout;
    CommonFunc::LayoutItems* _vLayout;
    FloatAnimation* _float;
};

#endif // TOOLBAR_H
