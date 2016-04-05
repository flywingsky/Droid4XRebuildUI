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
        QMenu,

        Title
    };

public:
    static QString StyleSheet(int type);


    explicit Qss(QObject *parent);

    void AddSheet(int type, bool cover = false);

    void Sync();



signals:

public slots:

private:


private:
    QWidget* _p;
    QString _sheet;

};

#endif // QSS_H
