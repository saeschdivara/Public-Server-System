#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include "public_server_system_globals.h"

namespace PublicServerSystem
{
namespace Rpc
{

class RpcClientPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT RpcClient : public QObject
{
        Q_OBJECT
    public:
        explicit RpcClient(QObject *parent = 0);
        virtual ~RpcClient();

        void setHost(const QString & name);

    protected:
        RpcClient(RpcClientPrivate * ptr, QObject *parent);
        RpcClientPrivate * d_ptr;

    private:
        Q_DECLARE_PRIVATE(RpcClient)
};

}
}

#endif // RPCCLIENT_H
