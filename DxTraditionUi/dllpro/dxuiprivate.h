#ifndef DXUIPRIVATE_H
#define DXUIPRIVATE_H

#include <QObject>
#include <QtGlobal>
#include "iuiproperty.h"

class DxUi;
class MainPanel;
class ToolBar;


class DxUiPrivate : public QObject , public IUiProperty
{
    Q_OBJECT
public:

    MainPanel* _mainPanel;
    ToolBar* _toolbar;


public:
    explicit DxUiPrivate(DxUi* q);


// 继承的属性接口
public:
    virtual WId ScreenId() const;

    virtual QSize PanelSize() const;
    virtual void SetPanelSize(QSize s);

    virtual QPoint PanelPos() const;
    virtual void setPanelPos(QPoint p);

    virtual QSize ScreenSize() const;

    // 设置screen等比缩放的一个比例。忽略横竖屏，只需要一个比例
    virtual QSize Scale() const;
    virtual void SetScale(QSize v);

    // 显示和隐藏主窗口 类似 show() hide()
    virtual void SetVisible(bool visible);
    virtual bool Visible() const;

    // 设置旋转度
    virtual void SetRotation(int r);


signals:

public slots:

private:
    DxUi* q_ptr;
    Q_DECLARE_PUBLIC(DxUi)
};

#endif // DXUIPRIVATE_H
