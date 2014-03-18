#ifndef WEBLOG_H
#define WEBLOG_H

#include <system/web/model/AbstractModel.h>
#include <system/web/model/ModelManager.h>

namespace PublicServerSystem
{
namespace Web
{
namespace Model
{
namespace Logger
{

class WebLogPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT WebLog : public AbstractModel
{
        Q_OBJECT
        Q_PROPERTY(QString ip READ ip WRITE setIP)
        Q_PROPERTY(QString host READ host WRITE setHost)
    public:
        WebLog(QObject *parent = 0);
        WebLog(arangodb::Document * doc, QObject *parent = 0);

        void setIP(const QString & ip);
        QString ip() const;

        void setHost(const QString & host);
        QString host() const;

        PU_DECLARE_MANAGER(WebLog);

    private:
        Q_DECLARE_PRIVATE(WebLog)
};

}
}
}
}

Q_DECLARE_METATYPE(PublicServerSystem::Web::Model::Logger::WebLog)

#endif // WEBLOG_H
