#ifndef DPITRANSFORM_H
#define DPITRANSFORM_H

#include <QObject>

class DpiTransform : public QObject
{
    Q_OBJECT
public:
    static void Transform();
public:
    explicit DpiTransform(QObject *parent = 0);

signals:

public slots:

};

#endif // DPITRANSFORM_H
