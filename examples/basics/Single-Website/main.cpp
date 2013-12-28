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

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>

#include <system/core/System.h>
#include <system/web/Server.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    PublicServerSystem::Core::System sys(&app);

    // Commandline arguments
    QStringList arguments = app.arguments();

    PublicServerSystem::Web::Server * webserver = new PublicServerSystem::Web::Server;
    // Now listens to both http and https requests not on the default ports
    // Normal http server
    webserver->listenOnNormalConnections(QHostAddress::Any, 8080);

    // Https server
    QFile certificateFile(arguments.at(1));
    certificateFile.open(QIODevice::ReadOnly);

    QFile keyFile(arguments.at(2));
    keyFile.open(QIODevice::ReadOnly);

    QSslCertificate certificate(&certificateFile);
    QSslKey key(&keyFile, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, arguments.at(3).toUtf8());

    qDebug() << certificate << "\n" << key << "\n" << arguments;
    webserver->setPrivateKey(key);
    webserver->setLocalCertificate(certificate);
    webserver->listenOnSecureConnections(QHostAddress::Any, 9080);

    certificateFile.close();
    keyFile.close();

    // Add server to the system
    sys.addServer(webserver);

    return sys.startUp();
}
