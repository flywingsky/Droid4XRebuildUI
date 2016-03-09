#ifndef IUIPROPERTY_H
#define IUIPROPERTY_H

#include <QWidget>
#include <QSize>

class IUiProperty
{
public:
    virtual WId ScreenId() const = 0;

    virtual QSize PanelSize() const = 0;
    virtual QSize SetPanelSize(QSize s) = 0;

    virtual QPoint PanelPos() const = 0;
    virtual void setPanelPos(QPoint p) = 0;

    virtual QSize ScreenSize() const = 0;

};

#endif // IUIPROPERTY_H
