#ifndef MAIL_H
#define MAIL_H

#include "public_server_system_globals.h"

namespace PublicServerSystem
{
namespace Email
{

class MailPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT Mail
{
    public:
        Mail();

    protected:
        MailPrivate * d_ptr;

    private:
        Q_DECLARE_PRIVATE(Mail)
};

}
}

#endif // MAIL_H
