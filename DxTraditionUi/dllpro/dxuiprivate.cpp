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
    if(_mainPanel)
    {
        return _mainPanel->GetScreen()->winId();
    }

    return NULL;
}


QSize DxUiPrivate::PanelSize() const
{
    if(_mainPanel)
    {
        return _mainPanel->size();
    }

    return QSize();
}

QSize DxUiPrivate::SetPanelSize(QSize s)
{
    if(_mainPanel)
    {
        _mainPanel->resize(s);
        return _mainPanel->size();
    }

    return QSize();
}

QPoint DxUiPrivate::PanelPos() const
{
    if(_mainPanel)
    {
        return _mainPanel->pos();
    }

    return QPoint();

}

void DxUiPrivate::setPanelPos(QPoint p)
{
    if(_mainPanel)
    {
        _mainPanel->move(p);
    }
}

QSize DxUiPrivate::ScreenSize() const
{
    if(_mainPanel)
    {
        return _mainPanel->GetScreen()->size();
    }

    return QSize();
}
