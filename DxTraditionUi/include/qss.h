#ifndef QSS_H
#define QSS_H

#include <QObject>



class Qss : public QObject
{
    Q_OBJECT
public:
    enum QssType
    {
        QListWidget,
        QLineEdit,
        ScrollBar,
        QPushButton,
        QDialog,
        QLabel,
        QMenu
    };

public:
    explicit Qss(QObject *parent);

    void AddSheet(int type, bool cover = false);

    void Sync();



signals:

public slots:

private:
    QString StyleSheet(int type) const;

private:
    QWidget* _p;
    QString _sheet;

};

#endif // QSS_H
