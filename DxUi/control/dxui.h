#ifndef DXUI_H
#define DXUI_H

#include <QObject>

class QListWidgetItem;
class MainPanel;

class DxUi : public QObject
{
    Q_OBJECT
public:
    explicit DxUi(QObject *parent = 0);

    MainPanel* CreatePanel();

signals:

public slots:
    void DragOutCreate(QListWidgetItem* it);


};

#endif // DXUI_H
