#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QDialog>

namespace Ui {
class MainPanel;
}

class QSplitter;
class Page;
class FramelessResize;

class MainPanel : public QDialog
{
    Q_OBJECT

public:
    explicit MainPanel(QWidget *parent = 0);
    ~MainPanel();

    int AddPage(Page* p);

protected slots:
    void OffsetSize(QMargins g);

private:
    Ui::MainPanel *ui;
    QSplitter* _splitter;
    FramelessResize* _fSize;
};

#endif // MAINPANEL_H
