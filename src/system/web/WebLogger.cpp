#include "WebLogger.h"
#include "model/logger/WebLog.h"

namespace PublicServerSystem
{
namespace Web
{

using namespace Model::Logger;

Q_GLOBAL_STATIC(WebLogger, globalLoggerFromTheWeb)

WebLogger *WebLogger::globalInstance()
{
    WebLogger * logger = globalLoggerFromTheWeb();
    return logger;
}

WebLogger::WebLogger()
{
    WebLog::objects->registerDatabaseModel();
}

void WebLogger::log(const QString &ip, const QString &host, const QString &requestPath, const QString &data)
{
    WebLog * logModel = WebLog::objects->create();
    logModel->setIP(ip);
    logModel->setHost(host);
    logModel->setPath(requestPath);

    logModel->saveAndDelete();
}

}
}
