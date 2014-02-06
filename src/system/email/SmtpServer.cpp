#include "SmtpServer.h"
#include <smtpclient.h>

#include <QtCore/QQueue>
#include <QtCore/QRunnable>
#include <QtCore/QThreadPool>

namespace PublicServerSystem
{
namespace Email
{

class SmtpServerPrivate
{
    public:
        QQueue<Mail *> mailQueue;
};

class Producer : public QRunnable
{
        // QRunnable interface
    public:
        void run() {
            //
        }
};

class Consumer : public QRunnable
{
        // QRunnable interface
    public:
        void run() {
            //
        }
};

SmtpServer::SmtpServer(QObject *parent) :
    QObject(parent),
    d_ptr(new SmtpServerPrivate)
{
}

}
}
