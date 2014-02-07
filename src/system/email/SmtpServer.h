#ifndef SMTPSERVER_H
#define SMTPSERVER_H

#include "system/rpc/Server.h"
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

    protected:
        SmtpServerPrivate * d_ptr;

    private:
        Q_DECLARE_PRIVATE(SmtpServer)
};

}
}

#endif // SMTPSERVER_H
