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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lpolarize-lib.1.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lpolarize-lib.1.0.0
else:unix: LIBS += -L$$PWD/../lib/ -lpolarize-lib.1.0.0

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
