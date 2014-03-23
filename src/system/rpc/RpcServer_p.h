#ifndef SERVER_P_H
#define SERVER_P_H

#include "public_server_system_globals.h"

// std
#include <functional>

// Qt
#include <QtWebServer.h>

namespace PublicServerSystem
{
namespace Rpc
{

class ServerPrivate
{
    public:
        QtWebServer * server;
        QList< QPair< QString, RpcCommandFunction > > commands;
};

}
}

#endif // SERVER_P_H
