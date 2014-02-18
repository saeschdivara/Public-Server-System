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

#ifndef SERVER_H
#define SERVER_H

#include "public_server_system_globals.h"

#include "system/core/ServerInterface.h"
#include "system/web/AbstractSite.h"

// Tufao
#include <httpserver.h>
#include <httpsserver.h>
// Qt
#include <QtNetwork/QHostAddress>

namespace PublicServerSystem
{
namespace Web
{

class ServerPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT Server : public QObject, public Core::ServerInterface
{
        Q_OBJECT
    public:
        explicit Server(QObject *parent = 0);
        virtual ~Server();

        void addWebsite(const QString & name, AbstractSite * site);

        // Normal listening
        bool listenOnNormalConnections(const QHostAddress &address = QHostAddress::Any,
                                       quint16 port = 80);

        void setStaticFilesDir(const QString & dir, const QString & websitePath);
        void setMediaDir(const QString & dir, const QString & websitePath);

        // Secure listening
        bool listenOnSecureConnections(const QHostAddress &address = QHostAddress::Any,
                                       quint16 port = 443);

        void setPrivateKey(const QSslKey &key);
        void setLocalCertificate(const QSslCertificate &certificate);

    protected:
        ServerPrivate * d_ptr;

    protected Q_SLOTS:
        void clientConnectionReady(Tufao::HttpServerRequest *request,
                                   Tufao::HttpServerResponse *response);

        bool serveStaticFile(Tufao::HttpServerRequest *request,
                              Tufao::HttpServerResponse *response, const QString &path);

    private:
        Q_DECLARE_PRIVATE(Server)
};

}
}

#endif // SERVER_H
