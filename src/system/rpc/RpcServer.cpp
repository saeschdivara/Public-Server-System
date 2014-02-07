#include "RpcServer.h"

#include "RpcServer_p.h"

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

void Server::addCommand(const QString &requestRegex)
{
    //
}

void Server::listen(const QHostAddress &address, quint16 port)
{
    Q_D(Server);
    d->server->listen(address, port);
}

Server::Server(ServerPrivate *ptr, QObject *parent) :
    QObject(parent),
    d_ptr(ptr)
{
    ptr->server = new Tufao::HttpServer;
}

}
}
