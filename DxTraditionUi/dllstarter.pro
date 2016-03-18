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
    ./Product \
    ./ProductD \
    ./uiproperty \
    ./lib \
    ./ui_ship \
    ./ui_nothing

SOURCES += dllstarter/main.cpp \
    ui_ship/ui_ship.cpp \
    ui_nothing/ui_nothing.cpp \
    ui_nothing/msgtest.cpp

HEADERS  += \
    dllpro/dllpro_global.h \
    dllpro/dxui.h \
    msgcenter/IMsgObsever.h \
    uiproperty/iuiproperty.h \
    msgcenter/msgdef.h \
    lib/ship.h \
    lib/shipdef.h \
    ui_ship/ui_ship.h \
    ui_nothing/ui_nothing.h \
    ui_nothing/msgtest.h


CONFIG(debug, debug|release) {
    DESTDIR += $$PWD/ProductD/
    LIBS += \
        $$PWD/ProductD/dllpro.lib \
        $$PWD/ProductD/D4xShip.lib \
} else {
    DESTDIR += $$PWD/Product/
    LIBS += \
        $$PWD/Product/dllpro.lib \
        $$PWD/Product/D4xShip.lib \
}
