#-------------------------------------------------
#
# Project created by QtCreator 2016-03-03T16:38:13
#
#-------------------------------------------------

QT       += widgets

TARGET = dllpro
TEMPLATE = lib

DEFINES += DLLPRO_LIBRARY

INCLUDEPATH += \
    ./dllpro \
    ./mainpanel \
    ./title \
    ./screen \
    ./include \
    ./toolbar \
    ./msgcenter

SOURCES += \
    toolbar/toolbar.cpp \
    title/title.cpp \
    screen/screen.cpp \
    msgcenter/ReadWriteLocker.cpp \
    msgcenter/UIMsgMgr.cpp \
    mainpanel/mainpanel.cpp \
    include/framelessmove.cpp \
    include/framelessresize.cpp \
    include/path.cpp \
    include/qss.cpp \
    dllpro/dxui.cpp

HEADERS +=\
        dllpro/dllpro_global.h \
    toolbar/toolbar.h \
    title/title.h \
    screen/screen.h \
    msgcenter/IMsgObsever.h \
    msgcenter/ReadWriteLocker.h \
    msgcenter/UIMsgMgr.h \
    mainpanel/mainpanel.h \
    include/framelessmove.h \
    include/framelessresize.h \
    include/path.h \
    include/qss.h \
    dllpro/dxui.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    toolbar/toolbar.ui \
    title/title.ui \
    screen/screen.ui \
    mainpanel/mainpanel.ui


CONFIG(debug, debug|release) {
    DESTDIR += $$PWD/ProductD/
} else {
    DESTDIR += $$PWD/Product/
}
