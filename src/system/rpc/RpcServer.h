#ifndef RPCSERVER_H
#define RPCSERVER_H

#include "public_server_system_globals.h"

#include "system/core/ServerInterface.h"

// std
#include <functional>

// Tufao
#include <httpserver.h>

// Qt
#include <QtNetwork/QHostAddress>

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

        virtual void listen(const QHostAddress & address = QHostAddress::Any, quint16 port = 7210);

        void addCommand(const QString &requestRegex, RpcCommandFunction fnc);

    protected:
        Server(ServerPrivate * ptr, QObject *parent = 0);
        ServerPrivate * d_ptr;

    protected Q_SLOTS:
        void handleConnection(Tufao::HttpServerRequest * request, Tufao::HttpServerResponse * response);

    private:
        Q_DECLARE_PRIVATE(Server)
};

template<typename Obj, typename Result, typename ...Args>
struct Delegate
{
        Obj * x;
        Result (Obj::*f)(Args...);
        template<typename ...Ts>
        Result operator()(Ts&&... args) {
            return (x->*f)(std::forward<Ts>(args)...);
        }
};

template<typename Obj, typename Result, typename ...Args>
auto make_delegate( Obj * x, Result (Obj::*fun)(Args...)) ->
    Delegate<Obj, Result, Args...>
{
    Delegate<Obj, Result, Args...> result{x, fun};
    return result;
}

}
}

#endif // RPCSERVER_H
