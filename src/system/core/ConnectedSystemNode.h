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
    public:
        ConnectedSystemNode(QCoreApplication * app);
        virtual ~ConnectedSystemNode();

    protected:
        ConnectedSystemNodePrivate * d_ptr;

    private:
        Q_DECLARE_PRIVATE(ConnectedSystemNode)
};

}
}

#endif // CONNECTEDSYSTEMNODE_H
