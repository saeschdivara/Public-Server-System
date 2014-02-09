#include "RpcServer.h"

#include "RpcServer_p.h"

// Tufao
#include <headers.h>
#include <httpserverrequest.h>
#include <httpserverresponse.h>
#include <url.h>

// Qt
#include <QtCore/QBuffer>
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
    d_ptr->server->close();

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

    QObject::connect( d->server, &Tufao::HttpServer::requestReady,
                      this, &Server::handleConnection
                      );
}

Server::Server(ServerPrivate *ptr, QObject *parent) :
    QObject(parent),
    d_ptr(ptr)
{
    ptr->server = new Tufao::HttpServer;
}

void Server::handleConnection(Tufao::HttpServerRequest *request, Tufao::HttpServerResponse *response)
{
    Q_D(Server);

    Tufao::Url url(Tufao::Url::url(request));
    Tufao::Headers headers = request->headers();

    QString hostname = url.hostname();
    QString urlPath = url.path();

    for( QPair< QString, RpcCommandFunction > pair : d->commands ) {
        QString regexString = pair.first;

        QRegularExpression re(regexString);
        QRegularExpressionMatch match = re.match(urlPath);
        bool hasMatch = match.hasMatch();

        if (hasMatch) {
            auto commandFunction = pair.second;

            QByteArray postData = request->body();
            QByteArray method = request->method();

            QBuffer buffer;
            buffer.open(QIODevice::ReadWrite);

            QTextStream stream(&buffer);

            stream.setCodec(QTextCodec::codecForName("UTF-8"));

            stream << commandFunction(method, postData);

            buffer.close();

            QByteArray renderedView = buffer.data();

            response->writeHead(Tufao::HttpServerResponse::OK);
            response->end(renderedView);

            return;
        }
    }

    response->writeHead(Tufao::HttpServerResponse::NOT_FOUND);
    response->end("Not found");
}

}
}
