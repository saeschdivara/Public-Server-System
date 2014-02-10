#include "SmtpServer.h"
#include "system/rpc/RpcServer_p.h"

// Smptp Client
#include <smtpclient.h>

// Qt
#include <QtCore/QJsonDocument>
#include <QtCore/QQueue>
#include <QtCore/QRunnable>
#include <QtCore/QThreadPool>

#include <functional>

namespace PublicServerSystem
{
namespace Email
{

class SmtpServerPrivate : public Rpc::ServerPrivate
{
    public:
        QQueue<Mail *> mailQueue;
};

class Producer : public QRunnable
{
    public:
        Producer(SmtpServerPrivate * smtpPrivate) :
            m_serverPrivate(smtpPrivate)
        {
        }

        virtual void run() {
            //
        }

    protected:
        SmtpServerPrivate * m_serverPrivate;
};

class Consumer : public QRunnable
{
    public:
        Consumer(SmtpServerPrivate * smtpPrivate) :
            m_serverPrivate(smtpPrivate)
        {
        }

        virtual void run() {
            //
        }

    protected:
        SmtpServerPrivate * m_serverPrivate;
};

SmtpServer::SmtpServer(QObject *parent) :
    Rpc::Server(new SmtpServerPrivate, parent)
{
}

void SmtpServer::listen(const QHostAddress &address, quint16 port)
{
    Rpc::Server::listen(address, port);

    addCommand("^/email/send/", Rpc::make_delegate(this, &SmtpServer::sendEmailRpc));
}

QString SmtpServer::sendEmailRpc(QByteArray method, QByteArray postData)
{
    postData = "";
    postData += "{";
    postData +=     "\"\"";
    postData += "";
    postData += "}";

    qDebug() << "ddd";

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(postData, &error);

    if (error.error == QJsonParseError::NoError || true) {
        SmtpClient client("mx.netzone.ch");
        MimeMessage email;

        MimePart content;
        content.setContent("HAAAALLLOOO");

        EmailAddress address("sascha.haeusler@netzbarkeit.ch", "Sascha Hauesler");
        email.addTo(&address);
        email.setSubject("Hallo");
        email.setContent(&content);

        client.connectToHost();
        if ( ! client.sendMail(email) ) {
            qDebug() << client.getResponseCode() << client.getResponseText();
        }
    }

    return QString();
}

}
}
