#include "UserSession.h"

#include <headers.h>
#include <url.h>

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
    get = query.queryItems();
}

}
}
