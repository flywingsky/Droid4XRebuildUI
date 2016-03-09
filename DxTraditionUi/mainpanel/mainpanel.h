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

class MainPanel : public QDialog
{
    Q_OBJECT

public:
    explicit MainPanel(QWidget *parent = 0);
    ~MainPanel();

    Screen* GetScreen() const;

    // 固定尺寸拖拽的比例。值无所谓，重要的是w/h。如果其中之一为0，则自由拖拽
    void SetScale(QSize s);

    void SetToolbar(QWidget* t);

public slots:
    void ReverseMaxStatus();


protected:
    void resizeEvent(QResizeEvent *event);
private:
    void InitTitle();
    void InitFocusWidget();
    void SetToolbarDockArea(Qt::DockWidgetArea postion);
    void RelayoutToolbar();

private slots:
    void DragMove(QPoint offset);

private:
    Ui::MainPanel *ui;
    FramelessMove* _move;
    FramelessResize* _resize;
    FocusWidget* _focus;
    QWidget* _toolbar;

};

#endif // MAINPANEL_H
