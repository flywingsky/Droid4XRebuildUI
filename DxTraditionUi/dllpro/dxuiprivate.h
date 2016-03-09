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
    virtual QSize SetPanelSize(QSize s);

    virtual QPoint PanelPos() const;
    virtual void setPanelPos(QPoint p);

    virtual QSize ScreenSize() const;

signals:

public slots:

private:
    DxUi* q_ptr;
    Q_DECLARE_PUBLIC(DxUi)
};

#endif // DXUIPRIVATE_H
