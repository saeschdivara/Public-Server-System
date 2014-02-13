#include "RpcClient.h"
#include "RpcClient_p.h"

namespace PublicServerSystem
{
namespace Rpc
{

RpcClient::RpcClient(QObject *parent) :
    RpcClient(new RpcClientPrivate, parent)
{
}

RpcClient::~RpcClient()
{
    delete d_ptr;
}

void RpcClient::setHost(const QString &name)
{
    Q_D(RpcClient);
    d->hostname = name;
}

RpcClient::RpcClient(RpcClientPrivate *ptr, QObject *parent) :
    QObject(parent),
    d_ptr(ptr)
{
    //
}

}
}
