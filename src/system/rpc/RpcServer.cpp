#include "RpcServer.h"

#include "RpcServer_p.h"

// Qt
#include <QtCore/QBuffer>
#include <QtCore/QDebug>
#include <QtCore/QRegularExpression>
#include <QtCore/QTextCodec>

namespace PublicServerSystem
{
namespace Rpc
{

Server::Server(QObject *parent) :
    Server(new ServerPrivate, parent)
{
}

Server::~Server()
{
    delete d_ptr->server;
    delete d_ptr;
}

void Server::addCommand( QString requestRegex, RpcCommandFunction fnc)
{
    Q_D(Server);
    d->commands.append(qMakePair< QString, RpcCommandFunction >(requestRegex, fnc));
}

void Server::listen(const QHostAddress &address, quint16 port)
{
    Q_D(Server);
    d->server->listen(address, port);

    QObject::connect( d->server, &QtWebServer::clientConnectionReady,
                      this, &Server::handleConnection
                      );
}

Server::Server(ServerPrivate *ptr, QObject *parent) :
    QObject(parent),
    d_ptr(ptr)
{
    ptr->server = new QtWebServer;
}

void Server::handleConnection(QtWebRequest *request, QtWebResponse *response)
{
    Q_D(Server);

    QString urlPath = request->requestPath();

    for( QPair< QString, RpcCommandFunction > pair : d->commands ) {
        QString regexString = pair.first;

        QRegularExpression re(regexString);
        QRegularExpressionMatch match = re.match(urlPath);
        bool hasMatch = match.hasMatch();

        if (hasMatch) {
            auto commandFunction = pair.second;

            QByteArray postData = ""; //request->body();
            QtWebRequest::RequestMethod requestMethod = request->method();

            QByteArray method;

            if ( requestMethod == QtWebRequest::RequestMethod::Get ) {
                method = "GET";
            }

            QBuffer buffer;
            buffer.open(QIODevice::ReadWrite);

            QTextStream stream(&buffer);

            stream.setCodec(QTextCodec::codecForName("UTF-8"));

            stream << commandFunction(method, postData);

            buffer.close();

            QByteArray renderedView = buffer.data();

            response->setStatus(QtWebResponse::StatusCode::OK);
            response->write(renderedView);
            response->end();

            return;
        }
    }

    response->setStatus(QtWebResponse::StatusCode::NOT_FOUND);
    response->end();
}

}
}
