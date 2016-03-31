#ifndef IUIPROPERTY_H
#define IUIPROPERTY_H

#include <QWidget>
#include <QSize>

class IUiProperty
{
public:
    virtual WId ScreenId() const = 0;

    virtual QSize PanelSize() const = 0;
    virtual void SetPanelSize(QSize s) = 0;

    virtual QPoint PanelPos() const = 0;
    virtual void setPanelPos(QPoint p) = 0;

    virtual QSize ScreenSize() const = 0;

    // 设置screen等比缩放的一个比例。忽略横竖屏，只需要一个比例
    virtual QSize Scale() const = 0;
    virtual void SetScale(QSize v) = 0;

    // 显示和隐藏主窗口 类似 show() hide()
    virtual void SetVisible(bool visible) = 0;
    virtual bool Visible() const = 0;

    // 调整主窗口，会根据比例调整，以及放置到屏幕中间
    virtual void Adjust() const = 0;

    // 设置旋转度
    virtual void SetRotation(int r) = 0;


};

#endif // IUIPROPERTY_H
