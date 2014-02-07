#ifndef SERVER_P_H
#define SERVER_P_H

#include <httpserver.h>

namespace PublicServerSystem
{
namespace Rpc
{

class ServerPrivate
{
    public:
        Tufao::HttpServer * server;
};

}
}

#endif // SERVER_P_H
