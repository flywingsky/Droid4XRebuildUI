#ifndef FRAMELESSMOVE_H
#define FRAMELESSMOVE_H

#include <QObject>
#include <qpoint.h>

class QWidget;

/**
 * @brief The FramelessMove class
 *        无windows边框移动窗口的托管类
 *
 *        将需要无边框移动的窗口指针，作为此类的parent指针
 *        移动窗口的工作，就可以交给此类。
 */

class FramelessMove : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief SetFrameLess 设定无边框，将目标窗口设定为无边框属性。
     * @param less true无边框，false有边框
     */
    static void SetFrameLess(bool less, QWidget* target);

public:
    explicit FramelessMove(QWidget *parent = 0);

    /**
     * @brief SetMonitor 设定监视目标，会截获该窗口的mouse事件，作为触发拖动窗口的事件
     * @param monitor 目标窗口
     */
    void SetMonitor(QWidget* monitor);

    /**
     * @brief SetTarget 设定作用目标，拖动窗口最终会对target产生效果
     * @param target
     */
    void SetTarget(QWidget* target);

    /**
     * @brief SetFrameLess 设定无边框，将目标窗口设定为无边框属性。如果没有设定target则无任何作用
     * @param less true无边框，false有边框
     */
    void SetFrameLess(bool less);


signals:
    void Pressed(QPoint pos);
    void Release(QPoint pos);
    void Offset(QPoint pos);


protected:
    bool eventFilter(QObject *obj, QEvent *ev);


private:
    QWidget* _monitor;
    QWidget* _target;

    bool lButtonPress;
    QPoint _offsetPos;

};

#endif // FRAMELESSMOVE_H
