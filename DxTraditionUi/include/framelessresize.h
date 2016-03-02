#ifndef FRAMELESSRESIZE_H
#define FRAMELESSRESIZE_H

#include <QMargins>
#include <QObject>

class QWidget;

class FramelessResize : public QObject
{
    Q_OBJECT
public:
    enum Direction {
        NONE = 0x0000,
        TOP = 0x0001,
        BOTTOM = 0x0002,
        LEFT = 0x0004,
        RIGHT = 0x0008,
        LEFTTOP = LEFT | TOP,
        LEFTBOTTOM = LEFT | BOTTOM,
        RIGHTBOTTOM = RIGHT | BOTTOM,
        RIGHTTOP = RIGHT | TOP
    };
public:
    explicit FramelessResize(QObject *parent = 0);

    void SetMonitor(QWidget* p);
    void SetTarget(QWidget* p);

    void SetBorderWidth(int w);
    int BorderWidth();


signals:
    void OffsetGeometry(QMargins geometry);

public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

private:
    int GetDirection(const QPoint pt) const;
    void SetCursor(int direction);
    void DragResize(QEvent* ev);

private:
    QWidget* _monitor;
    QWidget* _target;
    int _pressDirection;


    int _borderWidth;
};

#endif // FRAMELESSRESIZE_H
