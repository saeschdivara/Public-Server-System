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

        QList< QPair<QString, QString> > get() const {
            return m_get;
        }

        QHash<QString, QString> post() const {
            return m_post;
        }

    protected:
        QList< QPair<QString, QString> > m_get;
        QHash<QString, QString> m_post;
};

}
}

#endif // USERSESSION_H
