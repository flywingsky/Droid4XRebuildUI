#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QDialog>

namespace Ui {
class Toolbar;
}

class Toolbar : public QDialog
{
    Q_OBJECT

public:
    explicit Toolbar(QWidget *parent = 0);
    ~Toolbar();

private:
    Ui::Toolbar *ui;
};

#endif // TOOLBAR_H
