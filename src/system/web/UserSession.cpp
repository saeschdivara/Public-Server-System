#include "UserSession.h"

#include <headers.h>
#include <url.h>

#include <QtCore/QDebug>
#include <QtCore/QUrlQuery>

namespace PublicServerSystem
{
namespace Web
{

UserSession::UserSession(Tufao::HttpServerRequest *request, Tufao::HttpServerResponse *response)
{
    Tufao::Url url(Tufao::Url::url(request));
    Tufao::Headers headers = request->headers();

    QUrlQuery query(url.query());
    this->m_get = query.queryItems();

    QUrlQuery postQuery(QString(request->body()));
    for ( QPair<QString, QString> itemPair : postQuery.queryItems() ) {
        QString key = itemPair.first;
        QString value = itemPair.second;

        this->m_post.insert(key, value);
    }
}

}
}
