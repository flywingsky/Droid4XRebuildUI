#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

namespace Ui {
class Page;
}

class Title;
class Screen;

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = 0);
    ~Page();

    Title* TitleWidget();
    Screen* ScreenWidget();


private:
    Ui::Page *ui;
};

#endif // PAGE_H
