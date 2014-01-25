#ifndef CONNECTEDSYSTEMNODE_H
#define CONNECTEDSYSTEMNODE_H

#include "system/core/System.h"

namespace PublicServerSystem
{
namespace Core
{

class ConnectedSystemNodePrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT ConnectedSystemNode : public System
{
        Q_OBJECT
    public:
        ConnectedSystemNode(QCoreApplication * app);
        virtual ~ConnectedSystemNode();

        virtual void beforeStartUp();

    protected Q_SLOTS:
        void deceideToBeMaster();
        void receivedMessageFromMulticastGroup();

    private:
        Q_DECLARE_PRIVATE(ConnectedSystemNode)
};

}
}

#endif // CONNECTEDSYSTEMNODE_H
