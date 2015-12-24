#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QString>

class Path : public QObject
{
    Q_OBJECT
public:
    static Path* instance();


    QString DataDir();
    QString DesktopDir();
    QString ConfigDir();
    QString ApplicationDir();


    QString OvaPath();
    QString DroidExePath();

signals:

public slots:

private:
    explicit Path(QObject *parent = 0);
    QString ConfirmPath(const QString path);

private:
    static Path* _instance;


};

#define PathObj Path::instance()

#endif // PATH_H
