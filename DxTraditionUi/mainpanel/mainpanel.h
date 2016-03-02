#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QDialog>

namespace Ui {
class MainPanel;
}

class FramelessMove;
class FramelessResize;

class MainPanel : public QDialog
{
    Q_OBJECT

public:
    explicit MainPanel(QWidget *parent = 0);
    ~MainPanel();

public slots:
    void ReverseMaxStatus();


private:
    void InitTitle();

private slots:
    void DragMove(QPoint offset);

private:
    Ui::MainPanel *ui;
    FramelessMove* _move;
    FramelessResize* _resize;
};

#endif // MAINPANEL_H
