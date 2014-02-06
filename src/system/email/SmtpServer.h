#ifndef SMTPSERVER_H
#define SMTPSERVER_H

#include "public_server_system_globals.h"

#include "system/core/ServerInterface.h"
#include "system/email/Mail.h"

namespace PublicServerSystem
{
namespace Email
{

class SmtpServerPrivate;

class SmtpServer : public Core::ServerInterface
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
