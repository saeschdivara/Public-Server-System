#include "SmtpServer.h"
#include "system/rpc/RpcServer_p.h"

// Smptp Client
#include <smtpclient.h>

// Qt
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

    addCommand("^/email/send/", std::bind(&SmtpServer::sendEmailRpc, this));
}

QString SmtpServer::sendEmailRpc()
{
    return QString();
}

}
}
