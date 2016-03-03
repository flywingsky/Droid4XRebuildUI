#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QDialog>

namespace Ui {
class ToolBar;
}

class ToolBar : public QDialog
{
    Q_OBJECT

public:
    explicit ToolBar(QWidget *parent = 0);
    ~ToolBar();

private slots:
    void testPost();
    void testSend();

private:
    Ui::ToolBar *ui;
};

#endif // TOOLBAR_H
