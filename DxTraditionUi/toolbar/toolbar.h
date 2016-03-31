#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QMap>
#include "commonfunc.h"

namespace Ui {
class ToolBar;
}

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QSpacerItem;

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
    void ButtonClicked();



private:
    Ui::ToolBar *ui;
    QMap<QString, QWidget*> _buttons;
    CommonFunc::LayoutItems* _hLayout;
    CommonFunc::LayoutItems* _vLayout;
};

#endif // TOOLBAR_H
