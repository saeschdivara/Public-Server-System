#ifndef SERVER_P_H
#define SERVER_P_H

#include "public_server_system_globals.h"

// std
#include <functional>

// Tufao
#include <httpserver.h>

namespace PublicServerSystem
{
namespace Rpc
{

class ServerPrivate
{
    public:
        Tufao::HttpServer * server;
        QList< QPair< QString, std::function<QString()> > > commands;
};

}
}

#endif // SERVER_P_H
