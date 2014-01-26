#ifndef SYSTEM_P_H
#define SYSTEM_P_H

#include "system/core/ConfigController.h"

#include <QtCore/QCoreApplication>

namespace PublicServerSystem
{
namespace Core
{

class SystemPrivate
{
    public:
        QCoreApplication *app;

        ConfigController config;
};

}
}

#endif // SYSTEM_P_H
