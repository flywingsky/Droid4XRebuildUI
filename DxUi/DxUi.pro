#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T10:26:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DxUi
TEMPLATE = app

INCLUDEPATH += ./widget \
    ./include \
    ./control


SOURCES += main.cpp \
    widget/mainpanel.cpp \
    include/framelessmove.cpp \
    include/path.cpp \
    include/qss.cpp \
    control/dxui.cpp \
    widget/title.cpp \
    widget/screen.cpp \
    widget/itemwidget.cpp \
    widget/switchablelistwidget.cpp \
    widget/pannel.cpp

FORMS += \
    widget/mainpanel.ui \
    widget/title.ui \
    widget/screen.ui \
    widget/itemwidget.ui

HEADERS += \
    widget/mainpanel.h \
    include/framelessmove.h \
    include/path.h \
    include/qss.h \
    control/dxui.h \
    widget/title.h \
    widget/screen.h \
    widget/itemwidget.h \
    widget/switchablelistwidget.h \
    widget/pannel.h

