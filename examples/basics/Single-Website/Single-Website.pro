#-------------------------------------------------
#
# Project created by QtCreator 2013-12-24T16:11:25
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Single-Website
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    LocalhostSite.cpp

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

CONFIG(release, debug|release): {
    LIBS += -L$$PWD/../../../dist/3rdparty/tufao/release/ -ltufao
    LIBS += -L$$PWD/../../../dist/3rdparty/arangodb-driver/release/ -larangodb-driver
    LIBS += -L$$PWD/../../../dist/3rdparty/grantlee/scriptable-library/release/ -lscriptabletags
    LIBS += -L$$PWD/../../../dist/Public-Server-System/release/ -lPublic-Server-System
}
else:CONFIG(debug, debug|release): {
    LIBS += -L$$PWD/../../../dist/3rdparty/tufao/debug/ -ltufao
    LIBS += -L$$PWD/../../../dist/3rdparty/arangodb-driver/debug/ -larangodb-driver
    LIBS += -L$$PWD/../../../dist/3rdparty/grantlee/scriptable-library/debug/ -lscriptabletags
    LIBS += -L$$PWD/../../../dist/Public-Server-System/debug/ -lPublic-Server-System
}

INCLUDEPATH += $$PWD/../../../3rdparty/tufao/src
DEPENDPATH += $$PWD/../../../3rdparty/tufao/src

INCLUDEPATH += $$PWD/../../../3rdparty/arangodb-driver/src
DEPENDPATH += $$PWD/../../../3rdparty/arangodb-driver/src

INCLUDEPATH += $$PWD/../../../3rdparty/grantlee/templates/
DEPENDPATH += $$PWD/../../../3rdparty/grantlee/templates/

INCLUDEPATH += $$PWD/../../../src/
DEPENDPATH += $$PWD/../../../src/

HEADERS += \
    LocalhostSite.h
