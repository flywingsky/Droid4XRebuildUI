#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QDialog>

namespace Ui {
class MainPanel;
}

class FramelessMove;
class QSplitter;

class MainPanel : public QDialog
{
    Q_OBJECT

public:
    explicit MainPanel(QWidget *parent = 0);
    ~MainPanel();

private:
    Ui::MainPanel *ui;
    FramelessMove* _frameMgr;
    QSplitter* _splitter;
};

#endif // MAINPANEL_H
