/********************************************************************************
 ** The MIT License (MIT)
 **
 ** Copyright (c) 2013 Sascha Ludwig Häusler
 **
 ** Permission is hereby granted, free of charge, to any person obtaining a copy of
 ** this software and associated documentation files (the "Software"), to deal in
 ** the Software without restriction, including without limitation the rights to
 ** use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 ** the Software, and to permit persons to whom the Software is furnished to do so,
 ** subject to the following conditions:
 **
 ** The above copyright notice and this permission notice shall be included in all
 ** copies or substantial portions of the Software.
 **
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 ** FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 ** COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 ** IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 ** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *********************************************************************************/

#include "Server.h"
#include "UserSession.h"
#include "WebLogger.h"

#include "system/core/Exception.h"

// Grantlee
#include <lib/cachingloaderdecorator.h>
// Tufao
#include <headers.h>
#include <httpfileserver.h>
#include <httpserverrequest.h>
#include <httpserverresponse.h>
#include <url.h>
// Qt
#include <QtCore/QBuffer>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QHash>
#include <QtCore/QTextCodec>
#include <QtCore/QTextStream>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>

namespace PublicServerSystem
{
namespace Web
{

class ServerPrivate
{
    public:
        // -----------[PROPERTIES] -----------
        QHash<QString, AbstractSite *> websites;
        // Servers
        QtWebServer * server = Q_NULLPTR;
        // Static files
        QString diskStaticFilesPath;
        QString staticFilesPath;
        // Media files
        QString diskMediaFilesPath;
        QString mediaFilesPath;
        // Secure data
        QSslKey privateKey;
        QSslCertificate certificate;

        // -----------[METHODS] -----------
        Grantlee::Context getSessionContext(QtWebRequest * request) {
            Grantlee::Context context;

            // Server
            context.insert("STATIC_URL",  QLatin1Char('/') + staticFilesPath + QLatin1Char('/'));
            context.insert("MEDIA_URL",  QLatin1Char('/') + mediaFilesPath + QLatin1Char('/'));

            context.insert("REQUEST_URL", request->requestPath());

            // Session
            //

            return context;
        }
};

Server::Server(QObject *parent) :
    QObject(parent),
    d_ptr(new ServerPrivate)
{
}

Server::~Server()
{
    delete d_ptr->server;
    delete d_ptr;
}

void Server::addWebsite(const QString &name, AbstractSite *site)
{
    Q_D(Server);
    d->websites.insert(name, site);
}

bool Server::listenOnNormalConnections(const QHostAddress &address, quint16 port)
{
    Q_D(Server);

    d->server = new QtWebServer;

    QObject::connect( d->server, &QtWebServer::clientConnectionReady,
                      this, &Server::onClientReady,
                      Qt::DirectConnection
                      );

    bool isListening = d->server->listen(address, port);

    if ( !isListening ) {
        qWarning() << "The server couldn't listen: " << d->server->errorString();
    }

    return isListening;
}

void Server::setStaticFilesDir(const QString &dir, const QString &websitePath)
{
    Q_D(Server);
    d->diskStaticFilesPath = dir;
    d->staticFilesPath = websitePath;
}

void Server::setMediaDir(const QString &dir, const QString &websitePath)
{
    Q_D(Server);
    d->diskMediaFilesPath = dir;
    d->mediaFilesPath = websitePath;
}

bool Server::listenOnSecureConnections(const QHostAddress &address, quint16 port)
{
    Q_D(Server);

    d->server = new QtWebServer;
    d->server->setSecure(true);

    QObject::connect( d->server, &QtWebServer::clientConnectionReady,
                      this, &Server::onClientReady,
                      Qt::DirectConnection
                      );

    bool isListening = d->server->listen(address, port);

    if ( !isListening ) {
        qWarning() << "The server couldn't listen: " << d->server->errorString();
    }

    return isListening;
//    if (!d->secureServer)
//        d->secureServer = new Tufao::HttpsServer(this);

//    QObject::connect( d->secureServer, &Tufao::HttpsServer::requestReady,
//                      this, &Server::clientConnectionReady
//                      );

//    // Set the necessary things before listening
//    d->secureServer->setPrivateKey(d->privateKey);
//    d->secureServer->setLocalCertificate(d->certificate);

//    bool isListening = d->secureServer->listen(address, port);

//    if (!isListening) {
//            qWarning() << "The server couldn't listen";
//        }

//    return isListening;
}

void Server::setPrivateKey(const QSslKey &key)
{
    Q_D(Server);
    d->privateKey = key;
}

void Server::setLocalCertificate(const QSslCertificate &certificate)
{
    Q_D(Server);
    d->certificate = certificate;
}

void Server::onClientReady(QtWebRequest *request, QtWebResponse *response)
{
    Q_D(Server);

    QHash<QByteArray, QByteArray> headers = request->headers();

    QList<QByteArray> splittedHost = headers.value("Host").split(':');

    QString hostname = splittedHost.first();
    QString urlPath = request->requestPath();
    QString ip = request->ip();

    AbstractSite * site = d->websites.value(hostname, Q_NULLPTR);

    QString logData("agent:%1\r\n");
    QString agent = headers.value("User-Agent");
    logData = logData.arg(agent);

    WebLogger::globalInstance()->log(ip, hostname, urlPath, logData);

    try {
        if (!site) throw Core::Exception(Core::ErrorCode::NotFound, QStringLiteral("The website doesn't exists"));

        if (urlPath.startsWith(QLatin1Char('/') + d->staticFilesPath + QLatin1Char('/'))) {
                serveStaticFile(request,
                                response,
                                d->diskStaticFilesPath,
                                d->staticFilesPath);
            }
        else if (urlPath.startsWith(QLatin1Char('/') + d->mediaFilesPath + QLatin1Char('/'))) {
                serveStaticFile(request,
                                response,
                                d->diskMediaFilesPath,
                                d->mediaFilesPath);
            }
        else {
                View::ViewInterface * view = site->view(urlPath);

                QBuffer buffer;
                buffer.open(QIODevice::ReadWrite);

                QTextStream stream(&buffer);

                stream.setCodec(QTextCodec::codecForName("UTF-8"));

                Grantlee::Context context = d->getSessionContext(request);
                context.setUrlType(Grantlee::Context::RelativeUrls);
                view->render(stream, site->templateEngine(), &context, request);

                buffer.close();

                QByteArray renderedView = buffer.data();

                response->setStatus(QtWebResponse::StatusCode::OK, "OK");
                response->write(renderedView);
                response->end();
            }
    }
    catch(Core::Exception ex) {
        response->setStatus(QtWebResponse::StatusCode::NOT_FOUND, ex.what());
        response->end();
    }
    catch (...) {
        response->setStatus(QtWebResponse::StatusCode::INTERNAL_SERVER_ERROR, "");
        response->end();
    }
}

bool Server::serveStaticFile(QtWebRequest *request,
                             QtWebResponse *response,
                             const QString &path,
                             const QString & staticPath)
{
    Q_D(Server);

    response->serveStaticFile(path, staticPath, request);

    return true;
}

}
}
