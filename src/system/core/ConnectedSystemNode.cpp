#include "ConnectedSystemNode.h"
#include "system/core/System_p.h"

namespace PublicServerSystem
{
namespace Core
{

class ConnectedSystemNodePrivate : public SystemPrivate
{
    public:
};

ConnectedSystemNode::ConnectedSystemNode(QCoreApplication *app) :
    System(new ConnectedSystemNodePrivate, app)
{
    //
}

ConnectedSystemNode::~ConnectedSystemNode()
{
}

}
}
