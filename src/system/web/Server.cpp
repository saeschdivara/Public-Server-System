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
        Tufao::HttpServer * normalServer = Q_NULLPTR;
        Tufao::HttpsServer* secureServer = Q_NULLPTR;
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
        Grantlee::Context getSessionContext(Tufao::HttpServerRequest * request, Tufao::HttpServerResponse * response) {
            Grantlee::Context context;

            // Server
            context.insert("STATIC_URL",  QLatin1Char('/') + staticFilesPath + QLatin1Char('/'));
            context.insert("MEDIA_URL",  QLatin1Char('/') + mediaFilesPath + QLatin1Char('/'));

            Tufao::Url url(Tufao::Url::url(request));
            context.insert("REQUEST_URL", url.path());

            // Session
            //

            return context;
        }

        UserSession * getSession(Tufao::HttpServerRequest * request, Tufao::HttpServerResponse * response) {
            return new UserSession(request, response);
        }
};

Server::Server(QObject *parent) :
    QObject(parent),
    d_ptr(new ServerPrivate)
{
}

Server::~Server()
{
    if(d_ptr->normalServer) d_ptr->normalServer->close();
    if(d_ptr->secureServer) d_ptr->secureServer->close();

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
    if (!d->normalServer)
        d->normalServer = new Tufao::HttpServer(this);

    QObject::connect( d->normalServer, &Tufao::HttpServer::requestReady,
                      this, &Server::clientConnectionReady
                      );

    bool isListening = d->normalServer->listen(address, port);

    if (!isListening) {
            qWarning() << "The server couldn't listen";
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
    if (!d->secureServer)
        d->secureServer = new Tufao::HttpsServer(this);

    QObject::connect( d->secureServer, &Tufao::HttpsServer::requestReady,
                      this, &Server::clientConnectionReady
                      );

    // Set the necessary things before listening
    d->secureServer->setPrivateKey(d->privateKey);
    d->secureServer->setLocalCertificate(d->certificate);

    bool isListening = d->secureServer->listen(address, port);

    if (!isListening) {
            qWarning() << "The server couldn't listen";
        }

    return isListening;
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

void Server::clientConnectionReady(Tufao::HttpServerRequest *request, Tufao::HttpServerResponse *response)
{
    Q_D(Server);

    Tufao::Url url(Tufao::Url::url(request));
    Tufao::Headers headers = request->headers();

    QString hostname = url.hostname();
    QString urlPath = url.path();
    QString ip = request->socket()->peerAddress().toString();

    AbstractSite * site = d->websites.value(hostname, Q_NULLPTR);

    QString logData("agent:%1\r\n");
    QString agent = headers.value("User-Agent");
    logData = logData.arg(agent);

    WebLogger::globalInstance()->log(ip, hostname, url.path(), logData);

    try {
        if (!site) throw Core::Exception(Core::ErrorCode::NotFound, QStringLiteral("The website doesn't exists"));

        if (urlPath.startsWith(QLatin1Char('/') + d->staticFilesPath + QLatin1Char('/'))) {
                if (!serveStaticFile(request, response, d->diskStaticFilesPath)) {
                        Core::Exception(Core::ErrorCode::NotFound, QStringLiteral("The file doesn't exists"));
                    }
            }
        else if (urlPath.startsWith(QLatin1Char('/') + d->mediaFilesPath + QLatin1Char('/'))) {
                if (!serveStaticFile(request, response, d->diskMediaFilesPath)) {
                        Core::Exception(Core::ErrorCode::NotFound, QStringLiteral("The file doesn't exists"));
                    }
            }
        else {
                View::ViewInterface * view = site->view(urlPath);

                UserSession * session = d->getSession(request, response);

                QBuffer buffer;
                buffer.open(QIODevice::ReadWrite);

                QTextStream stream(&buffer);

                stream.setCodec(QTextCodec::codecForName("UTF-8"));

                Grantlee::Context context = d->getSessionContext(request, response);
                view->render(stream, site->templateEngine(), &context, session);

                buffer.close();

                QByteArray renderedView = buffer.data();

                response->writeHead(Tufao::HttpServerResponse::OK);
                response->end(renderedView);
            }
    }
    catch(Core::Exception ex) {
        response->writeHead(Core::errorCodeToStatusCode(ex.code()));
        response->end(ex.what());
    }
    catch (...) {
        response->writeHead(Tufao::HttpServerResponse::INTERNAL_SERVER_ERROR);
        response->end("Error");
    }

}

bool Server::serveStaticFile(Tufao::HttpServerRequest *request, Tufao::HttpServerResponse *response, const QString & path)
{
    Q_D(Server);

    QString resource(QByteArray::fromPercentEncoding(Tufao::Url(request->url())
                                                     .path().toUtf8()));

    QString fileName(QDir::cleanPath(path
                                     + QDir::toNativeSeparators(resource)));


    fileName = fileName.replace("/" + d->staticFilesPath + "/", "/");
    fileName = fileName.replace("/" + d->mediaFilesPath + "/", "/");

    if (!fileName.startsWith(path + QDir::separator()))
        return false;

    {
        QFileInfo fileInfo(fileName);
        if (!fileInfo.exists() || !fileInfo.isFile())
            return false;
    }

    Tufao::HttpFileServer::serveFile(fileName, request, response);
    return true;
}

}
}
