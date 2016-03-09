#ifndef TITLE_H
#define TITLE_H

#include <QWidget>
#include <QMap>

namespace Ui {
class Title;
}

class QPushButton;


class Title : public QWidget
{
    Q_OBJECT

public:
    explicit Title(QWidget *parent = 0);
    ~Title();

    QPushButton *GetButton(QString name);

signals:
    void DoubleClicked();
    void DragStart();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent * event);


    void paintEvent(QPaintEvent *event);
private:
    void CreateButtons();



private:
    Ui::Title *ui;

    QMap<QString, QPushButton*> _buttons;
};

#endif // TITLE_H
