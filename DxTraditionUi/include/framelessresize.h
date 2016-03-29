#ifndef FRAMELESSRESIZE_H
#define FRAMELESSRESIZE_H

#include <QMargins>
#include <QObject>
#include <QSize>

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

    static QMargins FixRatioTransform(const QMargins &g, const QSize &scale, const QWidget *parent, const QWidget *elastic);
    static QSize ChangeRatioAdjust(const QSize& ratio, const QSize& parent, const QSize& byScale);

public:
    explicit FramelessResize(QObject *parent = 0);

    void SetMonitor(QWidget* p);
    void SetTarget(QWidget* p);

    void SetBorderWidth(int w);
    int BorderWidth();

    // 固定尺寸拖拽的比例。值无所谓，重要的是w/h。如果其中之一为0，则自由拖拽
    void SetScale(QSize s,  QWidget* elastic);
    QSize Scale() const;



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
    QWidget* _elastic;
    int _pressDirection;
    QSize _scale;




    int _borderWidth;
};

#endif // FRAMELESSRESIZE_H
