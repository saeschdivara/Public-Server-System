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

        QHash<QString, QString> get() const {
            return m_get;
        }

        QHash<QString, QString> post() const {
            return m_post;
        }

        QHash<QString, QString> files() const {
            return m_files;
        }

    protected:
        QHash<QString, QString> m_get;
        QHash<QString, QString> m_post;
        QHash<QString, QString> m_files;
};

}
}

#endif // USERSESSION_H
