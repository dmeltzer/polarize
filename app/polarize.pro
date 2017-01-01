QT += core widgets qml quick

CONFIG += c++11 qml_debug

TARGET = polarize
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
INCLUDEPATH += "$$PWD/../lib/"

SOURCES += main.cpp \
    mainapp.cpp \
    demooutput.cpp

HEADERS += \
    mainapp.h \
    demooutput.h

DISTFILES += \
    mainwindow.qml \
    PointInput.qml

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-polarize-lib-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/release/ -lpolarize-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-polarize-lib-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug/ -lpolarize-lib
else:unix: LIBS += -L$$PWD/../lib/ -lpolarize-lib.1.0.0

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

INCLUDEPATH += $$PWD/../build-polarize-lib-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug
DEPENDPATH += $$PWD/../build-polarize-lib-Desktop_Qt_5_7_0_MSVC2015_64bit-Debug/debug

RESOURCES += \
    polarize.qrc
