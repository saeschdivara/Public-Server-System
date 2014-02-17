#ifndef USERSESSION_H
#define USERSESSION_H

#include "public_server_system_globals.h"

#include <httpserverrequest.h>
#include <httpserverresponse.h>

#include <QtCore/QList>
#include <QtCore/QHash>

namespace PublicServerSystem
{
namespace Web
{

class UserSession
{
    public:
        UserSession(Tufao::HttpServerRequest * request, Tufao::HttpServerResponse * response);

        QList< QPair<QString, QString> > get;
        QHash<QString, QString> post;
};

}
}

#endif // USERSESSION_H
