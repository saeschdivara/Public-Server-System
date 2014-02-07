#include "Server.h"

#include "Server_p.h"

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
    delete d_ptr;
}

Server::Server(ServerPrivate *ptr, QObject *parent) :
    QObject(parent),
    d_ptr(ptr)
{
    //
}

}
}
