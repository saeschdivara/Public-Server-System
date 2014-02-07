#ifndef SERVER_H
#define SERVER_H

#include "public_server_system_globals.h"

#include "system/core/ServerInterface.h"

namespace PublicServerSystem
{
namespace Rpc
{

class ServerPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT Server : public QObject, public Core::ServerInterface
{
        Q_OBJECT
    public:
        explicit Server(QObject *parent = 0);
        virtual ~Server();

    protected:
        Server(ServerPrivate * ptr, QObject *parent = 0);
        ServerPrivate * d_ptr;

    private:
        Q_DECLARE_PRIVATE(Server)
};

}
}

#endif // SERVER_H
