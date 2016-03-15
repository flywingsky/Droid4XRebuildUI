#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QMap>

namespace Ui {
class ToolBar;
}

class QPushButton;

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = 0);
    ~ToolBar();

    void SetLandscape();
    void SetPortrait();

    QPushButton *GetButton(QString name);
protected:
    virtual void	paintEvent(QPaintEvent * event);
    virtual void	resizeEvent(QResizeEvent * event);

private:
    void CreateButtons();


private slots:



private:
    Ui::ToolBar *ui;
    QMap<QString, QPushButton*> _buttons;
};

#endif // TOOLBAR_H
