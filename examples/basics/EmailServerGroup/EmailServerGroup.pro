#-------------------------------------------------
#
# Project created by QtCreator 2014-02-10T12:20:12
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = EmailServerGroup
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

CONFIG(release, debug|release): {
    LIBS += -L$$PWD/../../../dist/3rdparty/tufao/release/ -ltufao
    LIBS += -L$$PWD/../../../dist/3rdparty/arangodb-driver/release/ -larangodb-driver
    LIBS += -L$$PWD/../../../dist/3rdparty/grantlee/template_library/release/ -ltemplate_library
    LIBS += -L$$PWD/../../../dist/Public-Server-System/release/ -lPublic-Server-System
}
else:CONFIG(debug, debug|release): {
    LIBS += -L$$PWD/../../../dist/3rdparty/tufao/debug/ -ltufao
    LIBS += -L$$PWD/../../../dist/3rdparty/arangodb-driver/debug/ -larangodb-driver
    LIBS += -L$$PWD/../../../dist/3rdparty/grantlee/template_library/debug/ -ltemplate_library
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

SOURCES += main.cpp
