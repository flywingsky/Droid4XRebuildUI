#ifndef SNAPSHOTPAGE_H
#define SNAPSHOTPAGE_H

#include <QDialog>

namespace Ui {
class SnapshotPage;
}

class SnapshotPage : public QDialog
{
    Q_OBJECT

public:
    explicit SnapshotPage(QWidget *parent = 0);
    ~SnapshotPage();

    void SetWidget(QWidget* p);


protected:
    virtual void paintEvent(QPaintEvent * event);


private:
    Ui::SnapshotPage *ui;
    QPixmap* _snapshot;
};

#endif // SNAPSHOTPAGE_H
