#ifndef SMTPSERVER_H
#define SMTPSERVER_H

#include "system/rpc/RpcServer.h"
#include "system/email/Mail.h"

namespace PublicServerSystem
{
namespace Email
{

class SmtpServerPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT SmtpServer : public Rpc::Server
{
        Q_OBJECT
    public:
        explicit SmtpServer(QObject *parent = 0);

    private:
        Q_DECLARE_PRIVATE(SmtpServer)
};

}
}

#endif // SMTPSERVER_H
