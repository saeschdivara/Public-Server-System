#include "ConnectedSystemNode.h"
#include "system/core/System_p.h"

#include <QtCore/QTimer>
#include <QtCore/QUuid>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>

namespace PublicServerSystem
{
namespace Core
{

enum class SystemState {
    Searching,
    Connected
};

const quint16 SERVER_MULTICAST_PORT = 45454;
const quint16 SERVER_TCP_PORT = 35353;
const QHostAddress MULTICAST_ADDRESS = QHostAddress("224.0.0.1");

class ConnectedSystemNodePrivate : public SystemPrivate
{
    public:
        // --------------------------- PROPERTIES -----------------------------
        QUdpSocket* udpSocket;

        QTcpSocket * tcpSocket = Q_NULLPTR;

        SystemState state = SystemState::Searching;
        bool isMasterNode = false;

        QHostAddress masterAddress;
        QUuid masterID;

        QHostAddress localAddress;
        QUuid localID;

        QTcpServer * server = Q_NULLPTR;

        // --------------------------- METHODS -----------------------------
        QHostAddress getAddress() {
            for ( QHostAddress address : QNetworkInterface::allAddresses() ) {
                    if (address != QHostAddress::LocalHost && address != QHostAddress::LocalHostIPv6) {
                            return address;
                        }
                }

            return QHostAddress::LocalHost;
        }
};

ConnectedSystemNode::ConnectedSystemNode(QCoreApplication *app) :
    System(new ConnectedSystemNodePrivate, app)
{
    Q_D(ConnectedSystemNode);
    d->udpSocket = new QUdpSocket(this);
}

ConnectedSystemNode::~ConnectedSystemNode()
{
    Q_D(ConnectedSystemNode);

    d->server->close();
}

void ConnectedSystemNode::beforeStartUp()
{
    Q_D(ConnectedSystemNode);

    d->localAddress = d->getAddress();
    d->localID = QUuid::createUuid();

    qDebug() << "My address:" << d->localAddress.toString();
    qDebug() << "My ID:" << d->localID.toByteArray();

    d->udpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, QVariant(1));

    d->udpSocket->bind(QHostAddress::AnyIPv4, SERVER_MULTICAST_PORT, QUdpSocket::ShareAddress);
    d->udpSocket->joinMulticastGroup(MULTICAST_ADDRESS); // https://en.wikipedia.org/wiki/Multicast_address

    QObject::connect( d->udpSocket, &QUdpSocket::readyRead,
                      this, &ConnectedSystemNode::receivedMessageFromMulticastGroup
                      );

    if (!d->isMasterNode) {
            QByteArray requestString("SEARCHING MASTER ");
            // Add IP
            requestString += d->localAddress.toString();
            // Add Uuid
            requestString += " " + d->localID.toByteArray();

            d->udpSocket->writeDatagram(requestString, MULTICAST_ADDRESS, SERVER_MULTICAST_PORT);
        }

    QTimer::singleShot( 2000, this, SLOT(deceideToBeMaster()) );
}

void ConnectedSystemNode::deceideToBeMaster()
{
    Q_D(ConnectedSystemNode);

    if (d->state == SystemState::Searching) {
            d->state = SystemState::Connected;
            d->isMasterNode =true;

            qDebug() << "Is now a master node";

            // Emit signal that this is master node
            Q_EMIT masterSignal();
        }
    else {
            qDebug() << "Is now slave node";

            // Emit signal that this is slave node
            Q_EMIT slaveSignal();
        }
}

void ConnectedSystemNode::receivedMessageFromMulticastGroup()
{
    Q_D(ConnectedSystemNode);

    if (d->udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(d->udpSocket->pendingDatagramSize());
            d->udpSocket->readDatagram(datagram.data(), datagram.size());

            qDebug() << datagram;

            if (d->isMasterNode && datagram.startsWith("SEARCHING MASTER")) {
                    datagram.replace("SEARCHING MASTER ", "");

                    QList<QByteArray> splitData = datagram.split(' ');

                    QString addressString = splitData.at(0);
                    QHostAddress address = QHostAddress(addressString);
                    QUuid id = QUuid(splitData.at(1));

                    QByteArray masterMessage("MASTER ");
                    masterMessage += id.toByteArray();
                    masterMessage += " " + d->localAddress.toString();
                    masterMessage += " " + d->localID.toByteArray();

                    d->udpSocket->writeDatagram(masterMessage, address, SERVER_MULTICAST_PORT);
                }

            if (!d->isMasterNode && datagram.startsWith("MASTER")) {
                    datagram.replace("MASTER ", "");

                    QList<QByteArray> splitData = datagram.split(' ');

                    QUuid localID = QUuid(splitData.at(0));

                    if (localID != d->localID) {
                            return;
                        }

                    d->state = SystemState::Connected;

                    QString addressString = splitData.at(1);
                    QHostAddress address = QHostAddress(addressString);
                    QUuid masterID = QUuid(splitData.at(2));

                    d->masterAddress = address;
                    d->masterID = masterID;

                    // We don't want the slaves to be in the multicast
                    d->udpSocket->leaveMulticastGroup(MULTICAST_ADDRESS);

                    QObject::disconnect( d->udpSocket, &QUdpSocket::readyRead,
                                         this, &ConnectedSystemNode::receivedMessageFromMulticastGroup
                                         );

                    delete d->udpSocket;
                }
        }
}

void ConnectedSystemNode::startToBeSlave()
{
    Q_D(ConnectedSystemNode);

    // We need a config from the master node
    d->config.discard();

    d->tcpSocket = new QTcpSocket(this);

    d->tcpSocket->connectToHost(d->masterAddress, SERVER_TCP_PORT);
}

void ConnectedSystemNode::startToBeMaster()
{
    Q_D(ConnectedSystemNode);

    d->server = new QTcpServer(this);
    d->server->listen(QHostAddress::Any, SERVER_TCP_PORT);
}

}
}
