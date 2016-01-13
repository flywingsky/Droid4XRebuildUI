#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <QDialog>

namespace Ui {
class MainPanel;
}

class QSplitter;
class PageData;
class FramelessResize;
class QListWidgetItem;
class SnapshotPage;

class MainPanel : public QDialog
{
    Q_OBJECT
public:
    explicit MainPanel(QWidget *parent = 0);
    ~MainPanel();

    int AddPage(PageData *d);



signals:
    void DragOut(QListWidgetItem* it);

private:
    QMargins FixRatioTransform(const QMargins& g);

private slots:
    void OffsetSize(QMargins g);
private:
    Ui::MainPanel *ui;
    QSplitter* _splitter;
    FramelessResize* _fSize;
    QSize _fixRatio;
};

#endif // MAINPANEL_H
