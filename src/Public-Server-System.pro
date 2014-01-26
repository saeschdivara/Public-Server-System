QT       += core network

QT       -= gui

TEMPLATE = lib

DEFINES += PUBLIC_SERVER_SYSTEM_LIBRARY

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

CONFIG(release, debug|release): {
    LIBS += -L$$PWD/../dist/3rdparty/tufao/release/ -ltufao
    LIBS += -L$$PWD/../dist/3rdparty/arangodb-driver/release/ -larangodb-driver
    LIBS += -L$$PWD/../dist/3rdparty/grantlee/template_library/release/ -ltemplate_library
}
else:CONFIG(debug, debug|release): {
    LIBS += -L$$PWD/../dist/3rdparty/tufao/debug/ -ltufao
    LIBS += -L$$PWD/../dist/3rdparty/arangodb-driver/debug/ -larangodb-driver
    LIBS += -L$$PWD/../dist/3rdparty/grantlee/template_library/debug/ -ltemplate_library
}

INCLUDEPATH += $$PWD/../3rdparty/tufao/src
DEPENDPATH += $$PWD/../3rdparty/tufao/src

INCLUDEPATH += $$PWD/../3rdparty/arangodb-driver/src
DEPENDPATH += $$PWD/../3rdparty/arangodb-driver/src

INCLUDEPATH += $$PWD/../3rdparty/grantlee/templates/
DEPENDPATH += $$PWD/../3rdparty/grantlee/templates/

HEADERS += \
    public_server_system_globals.h \
    system/core/System.h \
    system/core/ServerInterface.h \
    system/web/Server.h \
    system/web/AbstractSite.h \
    system/web/AbstractSite_p.h \
    system/web/view/ViewInterface.h \
    system/core/Exception.h \
    system/core/ConnectedSystemNode.h \
    system/core/System_p.h \
    system/core/ConfigController.h

SOURCES += \
    system/core/System.cpp \
    system/web/Server.cpp \
    system/web/AbstractSite.cpp \
    system/core/Exception.cpp \
    system/core/ConnectedSystemNode.cpp \
    system/core/ConfigController.cpp
