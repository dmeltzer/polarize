#-------------------------------------------------
#
# Project created by QtCreator 2016-12-21T22:17:24
#
#-------------------------------------------------

QT       += network gui core

TARGET = polarize-lib
TEMPLATE = lib

DEFINES += POLARIZELIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += polarizelib.cpp \
    src/polarpoint.cpp \
    src/terminalinput.cpp \
    src/etc-osc/OSCMessage.cpp \
    src/etc-osc/OSCNetworkManager.cpp \
    src/etc-osc/OSCParser.cpp

HEADERS += polarizelib.h\
        polarize-lib_global.h \
        src/polarpoint.h \
        src/inputinterface.h \
        src/terminalinput.h \
# From ETC S2L.
        src/etc-osc/OSCMessage.h \
        src/etc-osc/OSCNetworkManager.h \
        src/etc-osc/OSCParser.h
        src/etc-osc/utils.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
