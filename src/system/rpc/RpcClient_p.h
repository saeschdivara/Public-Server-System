#ifndef RPCCLIENT_P_H
#define RPCCLIENT_P_H

#include <QtNetwork/QNetworkAccessManager>

namespace PublicServerSystem
{
namespace Rpc
{

class RpcClientPrivate
{
    public:
        QString hostname;

        QNetworkAccessManager manager;
};

}
}

#endif // RPCCLIENT_P_H
