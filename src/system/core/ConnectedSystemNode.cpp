#include "ConnectedSystemNode.h"
#include "system/core/System_p.h"

#include <QtCore/QTimer>
#include <QtCore/QUuid>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
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

class ConnectedSystemNodePrivate : public SystemPrivate
{
    public:
        QUdpSocket* socket;

        SystemState state = SystemState::Searching;
        bool isMasterNode = false;

        QHostAddress masterAddress;
        QUuid masterID;

        QHostAddress localAddress;
        QUuid localID;

        QHostAddress getAddress() {
            for ( QHostAddress address : QNetworkInterface::allAddresses() ) {
                    if (address != QHostAddress::LocalHost && address != QHostAddress::LocalHostIPv6) {
                            return address;
                        }
                }
        }
};

ConnectedSystemNode::ConnectedSystemNode(QCoreApplication *app) :
    System(new ConnectedSystemNodePrivate, app)
{
    Q_D(ConnectedSystemNode);
    d->socket = new QUdpSocket(this);
}

ConnectedSystemNode::~ConnectedSystemNode()
{
}

void ConnectedSystemNode::beforeStartUp()
{
    Q_D(ConnectedSystemNode);

    d->localAddress = d->getAddress();
    d->localID = QUuid::createUuid();

    qDebug() << "My address:" << d->localAddress.toString();
    qDebug() << "My ID:" << d->localID.toByteArray();

    d->socket->setSocketOption(QAbstractSocket::MulticastLoopbackOption, QVariant(1));
    d->socket->bind(QHostAddress::AnyIPv4, SERVER_MULTICAST_PORT, QUdpSocket::ShareAddress);
    d->socket->joinMulticastGroup(QHostAddress("224.0.0.1")); // https://en.wikipedia.org/wiki/Multicast_address

    QObject::connect( d->socket, &QUdpSocket::readyRead,
                      this, &ConnectedSystemNode::receivedMessageFromMulticastGroup
                      );

    if (!d->isMasterNode) {
            QByteArray requestString("SEARCHING MASTER ");
            // Add IP
            requestString += d->localAddress.toString();
            // Add Uuid
            requestString += " " + d->localID.toByteArray();

            d->socket->writeDatagram(requestString, QHostAddress("224.0.0.1"), SERVER_MULTICAST_PORT);
        }

    QTimer::singleShot( 1000, this, SLOT(deceideToBeMaster()) );
}

void ConnectedSystemNode::deceideToBeMaster()
{
    Q_D(ConnectedSystemNode);

    if (d->state == SystemState::Searching) {
            d->isMasterNode =true;

            qDebug() << "Is now a master node";
        }
    else {
            qDebug() << "Is now slave node";
        }
}

void ConnectedSystemNode::receivedMessageFromMulticastGroup()
{
    Q_D(ConnectedSystemNode);

    if (d->socket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(d->socket->pendingDatagramSize());
            d->socket->readDatagram(datagram.data(), datagram.size());

            qDebug() << datagram;

            if (d->isMasterNode && datagram.startsWith("SEARCHING MASTER")) {
                    datagram.replace("SEARCHING MASTER ", "");

                    QList<QByteArray> splitData = datagram.split(' ');

                    QString addressString = splitData.at(0);
                    QHostAddress address = QHostAddress(addressString);
                    QUuid id = QUuid(splitData.at(1));

                    d->socket->connectToHost(address, SERVER_MULTICAST_PORT);

                    QByteArray masterMessage("MASTER ");
                    masterMessage += d->localAddress.toString();
                    masterMessage += " " + d->localID.toByteArray();

                    d->socket->write(masterMessage);
                }

            if (!d->isMasterNode && datagram.startsWith("MASTER")) {
                    d->state = SystemState::Connected;
                    datagram.replace("MASTER ", "");

                    QList<QByteArray> splitData = datagram.split(' ');

                    QString addressString = splitData.at(0);
                    QHostAddress address = QHostAddress(addressString);
                    QUuid id = QUuid(splitData.at(1));

                    d->masterAddress = address;
                    d->masterID = id;
                }
        }
}

}
}
