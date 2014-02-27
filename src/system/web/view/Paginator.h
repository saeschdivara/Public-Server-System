#ifndef PAGINATOR_H
#define PAGINATOR_H

#include "public_server_system_globals.h"

#include "system/web/model/AbstractModel.h"

#include <QtCore/QList>

namespace PublicServerSystem
{
namespace Web
{
namespace View
{

class PUBLICSERVERSYSTEMSHARED_EXPORT Paginator : public QObject
{
        Q_OBJECT
    public:
        Paginator(QList<Model::AbstractModel *> & list, QObject *parent = 0);
};

}
}
}

#endif // PAGINATOR_H
