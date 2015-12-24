#ifndef PANNEL_H
#define PANNEL_H

#include <QStackedWidget>

class Pannel : public QStackedWidget
{
    Q_OBJECT
public:
    explicit Pannel(QWidget *parent = 0);

signals:

public slots:
};

#endif // PANNEL_H
