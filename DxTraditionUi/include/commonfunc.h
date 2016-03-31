#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <QPair>
#include <QList>

class QLayout;
class QWidget;
class QRect;
class QGridLayout;
class QSize;


class CommonFunc
{
public:
    /// @brief 清空指定布局
    static void ClearLayout(QLayout &layout);
    static void ClearLayout(QLayout* layout);

    /// @brief 设置layout的space和margin都为0
    static void SetLayoutSpaceZero(QLayout& layout);

    /// @brief 判断是否为横屏
    static bool IsLandscape(QWidget* p);
    static bool IsLandscape(QSize& s);

    typedef QPair<QWidget*, QRect> LayoutWidget;
    typedef QList<LayoutWidget> LayoutItems;
    static void Relayout(LayoutItems &items, QGridLayout* l);
    static void Relayout(LayoutItems* items, QGridLayout* l);

    /// @brief 获得窗口所在屏幕的尺寸
    static QRect PrimaryScreenGeometry();
    static QRect CenterRect(QRect parent, QSize center);
};

#endif // COMMONFUNC_H
