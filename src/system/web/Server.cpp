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

// Tufao
#include <httpserverrequest.h>
#include <httpserverresponse.h>
// Qt
#include <QtCore/QHash>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>

namespace PublicServerSystem
{
namespace Web
{

class ServerPrivate
{
    public:
        QHash<QString, AbstractSite *> websites;
        // Servers
        Tufao::HttpServer * normalServer = Q_NULLPTR;
        Tufao::HttpsServer* secureServer = Q_NULLPTR;
        // Secure data
        QSslKey privateKey;
        QSslCertificate certificate;
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
            qWarning() << "The server couldn't listen (" << d->normalServer->errorString() << ")";
        }

    return isListening;
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
            qWarning() << "The server couldn't listen (" << d->secureServer->errorString() << ")";
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
    response->writeHead(Tufao::HttpServerResponse::NOT_FOUND);
    response->end("Not found");
}

}
}
