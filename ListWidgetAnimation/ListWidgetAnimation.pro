#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T10:55:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ListWidgetAnimation
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    itemwidget.cpp \
    switchablelistwidget.cpp \
    framelessmove.cpp

HEADERS  += dialog.h \
    itemwidget.h \
    switchablelistwidget.h \
    framelessmove.h

FORMS    += dialog.ui \
    itemwidget.ui
