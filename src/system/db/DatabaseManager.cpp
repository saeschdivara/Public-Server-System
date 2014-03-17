#include "DatabaseManager.h"

namespace PublicServerSystem
{
namespace Db
{

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

Q_GLOBAL_STATIC(arangodb::ArangoDBDriver, globalDriverInstance)

arangodb::ArangoDBDriver *DatabaseManager::driver()
{
    return globalDriverInstance();
}

}
}
