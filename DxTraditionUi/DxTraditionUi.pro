#-------------------------------------------------
#
# Project created by QtCreator 2016-03-01T16:53:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DxTraditionUi
TEMPLATE = app

INCLUDEPATH += \
    ./mainpanel \
    ./title \
    ./screen \
    ./include

SOURCES += main.cpp \
    mainpanel/mainpanel.cpp \
    title/title.cpp \
    screen/screen.cpp \
    include/framelessmove.cpp \
    include/framelessresize.cpp \
    include/path.cpp \
    include/qss.cpp

HEADERS  += \
    mainpanel/mainpanel.h \
    title/title.h \
    screen/screen.h \
    include/framelessmove.h \
    include/framelessresize.h \
    include/path.h \
    include/qss.h

FORMS    += \
    mainpanel/mainpanel.ui \
    title/title.ui \
    screen/screen.ui
