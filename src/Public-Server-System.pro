QT       += core

QT       -= gui

TEMPLATE = lib

DEFINES += PUBLIC_SERVER_SYSTEM_LIBRARY

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

CONFIG(release, debug|release): {
    LIBS += -L$$PWD/../dist/3rdparty/tufao/release/ -ltufao
    LIBS += -L$$PWD/../dist/3rdparty/arangodb-driver/release/ -larangodb-driver
    LIBS += -L$$PWD/../dist/3rdparty/grantlee/scriptable-library/release/ -lscriptabletags
}
else:CONFIG(debug, debug|release): {
    LIBS += -L$$PWD/../dist/3rdparty/tufao/debug/ -ltufao
    LIBS += -L$$PWD/../dist/3rdparty/arangodb-driver/debug/ -larangodb-driver
    LIBS += -L$$PWD/../dist/3rdparty/grantlee/scriptable-library/debug/ -lscriptabletags
}

INCLUDEPATH += $$PWD/../3rdparty/tufao/src
DEPENDPATH += $$PWD/../3rdparty/tufao/src

INCLUDEPATH += $$PWD/../3rdparty/arangodb-driver/src
DEPENDPATH += $$PWD/../3rdparty/arangodb-driver/src

INCLUDEPATH += $$PWD/../3rdparty/grantlee/src/
DEPENDPATH += $$PWD/../3rdparty/grantlee/src/

HEADERS += \
    public_server_system_globals.h
