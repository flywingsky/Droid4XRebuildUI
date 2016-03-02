#include "path.h"

#include <QStandardPaths>
#include <QDir>
#include <QApplication>

Path* Path::_instance = NULL;

Path *Path::instance()
{
    if (!_instance)
        _instance = new Path();
    return _instance;
}

Path::Path(QObject *parent) :
    QObject(parent)
{
}

QString Path::DataDir()
{
    return ConfirmPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation).replace("MultiMgr", "Droid4X"));
}


QString Path::DesktopDir()
{
    return ConfirmPath(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
}

QString Path::ConfigDir()
{
    return ConfirmPath(DataDir() + "config/");
}

QString Path::ApplicationDir()
{
    return ConfirmPath(QApplication::applicationDirPath());
}

QString Path::OvaPath()
{
    return ApplicationDir() + "ovas/droid4x.ova";
}

QString Path::DroidExePath()
{
    return ApplicationDir() + "Droid4X.exe";
}

QString Path::ConfirmPath(const QString path)
{
	QDir dir(path);
    if(dir.exists())
        return dir.absolutePath() + "/";

	dir.mkpath(dir.absolutePath());
	return dir.absolutePath() + "/";
}

