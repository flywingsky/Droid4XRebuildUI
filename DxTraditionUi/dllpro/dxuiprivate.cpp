#include "dxuiprivate.h"
#include "mainpanel.h"
#include "screen.h"

DxUiPrivate::DxUiPrivate(DxUi *q) :
    QObject(NULL),
    q_ptr(q),
    _mainPanel(NULL),
    _toolbar(NULL)
{
}


WId DxUiPrivate::ScreenId() const
{
    return _mainPanel->GetScreen()->winId();
}


QSize DxUiPrivate::PanelSize() const
{
    return _mainPanel->size();
}

void DxUiPrivate::SetPanelSize(QSize s)
{
    _mainPanel->resize(s);
}

QPoint DxUiPrivate::PanelPos() const
{
    return _mainPanel->pos();
}

void DxUiPrivate::setPanelPos(QPoint p)
{
    _mainPanel->move(p);
}

QSize DxUiPrivate::ScreenSize() const
{
    return _mainPanel->GetScreen()->size();
}

QSize DxUiPrivate::Scale() const
{
    return _mainPanel->Scale();
}

void DxUiPrivate::SetScale(QSize v)
{
    QSize temp;
    // 忽略旋转因素, 根据当前已经设置的横竖，来设置新的比例的横竖
    if(!_mainPanel->Scale().isEmpty())
    {
        if(_mainPanel->Scale().width() >= _mainPanel->Scale().height())
            temp = (v.width() > v.height()) ? v : QSize(v.height(),v.width());
        else
            temp = (v.width() < v.height()) ? v : QSize(v.height(),v.width());
    }
    else
        temp = v;

    _mainPanel->SetScale(temp);
}

void DxUiPrivate::SetVisible(bool visible)
{
    _mainPanel->setVisible(visible);
}

bool DxUiPrivate::Visible() const
{
    return !_mainPanel->isHidden();
}

void DxUiPrivate::SetRotation(int r)
{
    _mainPanel->SetRotate(r);
}
