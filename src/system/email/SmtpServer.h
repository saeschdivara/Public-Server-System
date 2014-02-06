#ifndef SMTPSERVER_H
#define SMTPSERVER_H

#include "public_server_system_globals.h"

#include "system/core/ServerInterface.h"

namespace PublicServerSystem
{
namespace Email
{

class SmtpServer : public Core::ServerInterface
{
        Q_OBJECT
    public:
        explicit SmtpServer(QObject *parent = 0);
};

}
}

#endif // SMTPSERVER_H
