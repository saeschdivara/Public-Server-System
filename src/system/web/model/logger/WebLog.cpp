#include "WebLog.h"
#include "system/web/model/AbstractModel_p.h"

int it_fooo = qRegisterMetaType<PublicServerSystem::Web::Model::Logger::WebLog>("WebLog");

namespace PublicServerSystem
{
namespace Web
{
namespace Model
{
namespace Logger
{

PU_DEFINE_MANAGER(WebLog)

class WebLogPrivate : public AbstractModelPrivate
{
    public:
};

WebLog::WebLog(QObject *parent) :
    AbstractModel(new WebLogPrivate, parent)
{
}

WebLog::WebLog(arangodb::Document *doc, QObject *parent) :
    AbstractModel(doc, new WebLogPrivate, parent)
{
}

void WebLog::setIP(const QString &ip)
{
    set("ip_address", ip);
}

QString WebLog::ip() const
{
    return get("ip_address").toString();
}

void WebLog::setHost(const QString &host)
{
    set("host", host);
}

QString WebLog::host() const
{
    return get("host").toString();
}

void WebLog::setPath(const QString &path)
{
    set("request_path", path);
}

QString WebLog::path() const
{
    return get("request_path").toString();
}

void WebLog::setData(const QString &data)
{
    set("extra_data", data);
}

QString WebLog::data() const
{
    return get("extra_data").toString();
}

void WebLog::setCreationDate(const QDateTime &time)
{
    set("created", time);
}

QDateTime WebLog::created() const
{
    return get("created").toDateTime();
}

}
}
}
}
