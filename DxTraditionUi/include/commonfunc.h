#ifndef COMMONFUNC_H
#define COMMONFUNC_H

class QLayout;
class QWidget;

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
};

#endif // COMMONFUNC_H
