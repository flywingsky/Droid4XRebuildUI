#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T14:51:34
#
#-------------------------------------------------

QT       += widgets

TARGET = QtExport
TEMPLATE = lib

DEFINES += QTEXPORT_LIBRARY

SOURCES += qtexport.cpp

HEADERS += qtexport.h\
        qtexport_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
