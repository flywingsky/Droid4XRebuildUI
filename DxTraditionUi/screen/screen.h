#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>

namespace Ui {
class Screen;
}

class Screen : public QWidget
{
    Q_OBJECT

public:
    explicit Screen(QWidget *parent = 0);
    ~Screen();

private:
    Ui::Screen *ui;
};

#endif // SCREEN_H
