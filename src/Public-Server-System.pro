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
    LIBS += -L$$PWD/../dist/3rdparty/smpt-client-qt/release/ -lSMTPEmail
}
else:CONFIG(debug, debug|release): {
    LIBS += -L$$PWD/../dist/3rdparty/tufao/debug/ -ltufao
    LIBS += -L$$PWD/../dist/3rdparty/arangodb-driver/debug/ -larangodb-driver
    LIBS += -L$$PWD/../dist/3rdparty/grantlee/template_library/debug/ -ltemplate_library
    LIBS += -L$$PWD/../dist/3rdparty/smpt-client-qt/debug/ -lSMTPEmail
}

INCLUDEPATH += $$PWD/../3rdparty/tufao/src/
DEPENDPATH += $$PWD/../3rdparty/tufao/src/

INCLUDEPATH += $$PWD/../3rdparty/arangodb-driver/src/
INCLUDEPATH += $$PWD/../3rdparty/arangodb-driver/include/
DEPENDPATH += $$PWD/../3rdparty/arangodb-driver/src/

INCLUDEPATH += $$PWD/../3rdparty/grantlee/templates/
DEPENDPATH += $$PWD/../3rdparty/grantlee/templates/

INCLUDEPATH += $$PWD/../3rdparty/smpt-client-qt/src/
DEPENDPATH += $$PWD/../3rdparty/smpt-client-qt/src/

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
    system/core/ConfigController.h \
    system/web/model/AbstractModel.h \
    system/web/model/AbstractModel_p.h \
    system/web/model/ModelManager.h \
    system/web/model/ModelManager_p.h \
    system/web/form/ModelForm.h \
    system/web/form/AbstractFormField.h \
    system/web/form/CharField.h \
    system/web/form/AbstractFormField_p.h \
    system/web/form/widget/WidgetInterface.h \
    system/web/form/widget/EmptyWidget.h \
    system/web/form/widget/TextInput.h \
    system/email/SmtpServer.h \
    system/email/Mail.h \
    system/rpc/RpcServer.h \
    system/rpc/RpcServer_p.h \
    system/rpc/RpcClient.h

SOURCES += \
    system/core/System.cpp \
    system/web/Server.cpp \
    system/web/AbstractSite.cpp \
    system/core/Exception.cpp \
    system/core/ConnectedSystemNode.cpp \
    system/core/ConfigController.cpp \
    system/web/model/AbstractModel.cpp \
    system/web/form/ModelForm.cpp \
    system/web/form/AbstractFormField.cpp \
    system/web/form/CharField.cpp \
    system/email/SmtpServer.cpp \
    system/email/Mail.cpp \
    system/rpc/RpcServer.cpp \
    system/rpc/RpcClient.cpp

OTHER_FILES += \
