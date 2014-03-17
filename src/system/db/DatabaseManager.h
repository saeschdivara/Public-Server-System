#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "public_server_system_globals.h"

#include <ArangoDBDriver.h>

namespace PublicServerSystem
{
namespace Db
{

class DatabaseManager : public QObject
{
        Q_OBJECT
    public:
        explicit DatabaseManager(QObject *parent = 0);

        static arangodb::ArangoDBDriver * driver();
};

}
}

#endif // DATABASEMANAGER_H
