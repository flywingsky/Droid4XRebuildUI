#ifndef PANEL_H
#define PANEL_H

#include <QStackedWidget>

class Panel : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = 0);

    void AddPage();

signals:

public slots:
};

#endif // PANEL_H
