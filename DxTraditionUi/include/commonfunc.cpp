#include "commonfunc.h"

#include <QLayout>
#include <QWidget>


void CommonFunc::ClearLayout(QLayout *layout)
{
    while(layout->count() > 0)
    {
        layout->removeItem(layout->itemAt(0));
    }
}

void CommonFunc::ClearLayout(QLayout &layout)
{
    ClearLayout(&layout);
}

void CommonFunc::SetLayoutSpaceZero(QLayout &layout)
{
    layout.setMargin(0);
    layout.setSpacing(0);
}

bool CommonFunc::IsLandscape(QWidget *p)
{
    return p->width() > p->height();
}
