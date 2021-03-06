#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QDialog>

namespace Ui {
class MainPanel;
}

class FramelessMove;
class FramelessResize;
class Screen;
class FocusWidget;
class ToolBar;

class MainPanel : public QDialog
{
    Q_OBJECT

public:
    explicit MainPanel(QWidget *parent = 0);
    ~MainPanel();

    Screen* GetScreen() const;

    // 固定尺寸拖拽的比例。值无所谓，重要的是w/h。如果其中之一为0，则自由拖拽
    void SetScale(QSize s);
    QSize Scale() const;

    void SetToolbar(ToolBar *t);

    void SetRotate(int r);

    void Rescale();




public slots:

    void ReverseMaxStatus();
    void ReverseFullStatus();

    // 目前是测试用接口，不用的时候要删掉
    void SetLandscape();
    void SetPortrait();


protected:
    void resizeEvent(QResizeEvent *event);
    virtual void	moveEvent(QMoveEvent * event);
    virtual void	changeEvent(QEvent * event);
    bool event(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *ev);
    virtual void	closeEvent(QCloseEvent * event);

private:
    void InitTitle();
    void InitFocusWidget();


    void SetToolbarDockArea(Qt::DockWidgetArea postion);
    void SetWithoutToolbarLayout(Qt::WindowStates ws);

    void ReverseTitleMaxBtn();

    // 初始化默认尺寸
    void InitNormalSize(bool Portrait, QSize scale);


private slots:
    void DragMove(QPoint offset);
    void RecodeNormalSize();

private:
    Ui::MainPanel *ui;
    FramelessMove* _move;
    FramelessResize* _resize;
    FocusWidget* _focus;
    ToolBar* _toolbar;
    QSize* _normalLandscape;
    QSize* _normalPortrait;
    QPoint* _normalPos;
    int _rotate;
    QSize _scale;

};

#endif // MAINPANEL_H
