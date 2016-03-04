#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T10:38:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dllstarter
TEMPLATE = app

INCLUDEPATH += \
    ./dllstarter \
    ./dllpro \
    ./msgcenter \
    ./Product
    ./ProductD

SOURCES += dllstarter/main.cpp

HEADERS  += \
    dllpro/dllpro_global.h \
    dllpro/dxui.h \
    msgcenter/IMsgObsever.h


CONFIG(debug, debug|release) {
    DESTDIR += $$PWD/ProductD/
    LIBS += \
        $$PWD/ProductD/dllpro.lib \
} else {
    DESTDIR += $$PWD/Product/
    LIBS += \
        $$PWD/Product/dllpro.lib \
}
