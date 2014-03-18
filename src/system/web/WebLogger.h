#ifndef WEBLOGGER_H
#define WEBLOGGER_H

#include "public_server_system_globals.h"

namespace PublicServerSystem
{
namespace Web
{

class PUBLICSERVERSYSTEMSHARED_EXPORT WebLogger : public QObject
{
        Q_OBJECT
    public:
        static WebLogger * globalInstance();
        WebLogger();

    public Q_SLOTS:
        void log(const QString & ip, const QString & host, const QString & requestPath, const QString & data );
};

}
}

#endif // WEBLOGGER_H
