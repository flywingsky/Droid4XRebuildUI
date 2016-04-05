#ifndef FLOATANIMATION_H
#define FLOATANIMATION_H

#include <QObject>
#include <QRect>

class QWidget;
class QState;
class QStateMachine;
class QPropertyAnimation;

class FloatAnimation : public QObject
{
    Q_OBJECT
public:
    explicit FloatAnimation(QObject *parent = 0);

    void SetMonitor(QWidget* p);
    void SetTarget(QWidget* t);

    void Start();
    void Stop();

signals:



public slots:


protected:
    bool eventFilter(QObject *obj, QEvent *ev);

private:
    void InitValue();

signals:
    void Show();
    void Hide();


private:
    QWidget* _monitor;
    QWidget* _target;

    QState* _show;
    QState* _hide;
    QPropertyAnimation* _hideAnim;
    QPropertyAnimation* _showAnim;
    QStateMachine* _machine;

    QRect _showTrigger;
    QRect _hideTrigget;
};

#endif // FLOATANIMATION_H
