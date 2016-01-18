#ifndef PANEL_H
#define PANEL_H

#include <QStackedWidget>


class Page;
class MainPanel;
class PageData;

class Panel : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = 0);

    Page* CurrentPage();

signals:
    void Empty();

public slots:
    void AddPage(PageData *d);
    void DeletePage(PageData* d);


private:

    MainPanel* _panel;

};

#endif // PANEL_H
