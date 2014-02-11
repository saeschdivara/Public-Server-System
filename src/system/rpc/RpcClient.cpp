#include "RpcClient.h"

namespace PublicServerSystem
{
namespace Rpc
{

RpcClient::RpcClient(QObject *parent) :
    QObject(parent)
{
}

RpcClient::~RpcClient()
{
    delete d_ptr;
}

}
}
