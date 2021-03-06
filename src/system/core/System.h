/********************************************************************************
 ** The MIT License (MIT)
 **
 ** Copyright (c) 2013 Sascha Ludwig Häusler
 **
 ** Permission is hereby granted, free of charge, to any person obtaining a copy of
 ** this software and associated documentation files (the "Software"), to deal in
 ** the Software without restriction, including without limitation the rights to
 ** use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 ** the Software, and to permit persons to whom the Software is furnished to do so,
 ** subject to the following conditions:
 **
 ** The above copyright notice and this permission notice shall be included in all
 ** copies or substantial portions of the Software.
 **
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 ** FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 ** COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 ** IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 ** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *********************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#include "public_server_system_globals.h"
#include "system/core/ServerInterface.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>

namespace PublicServerSystem
{
namespace Core
{

class SystemPrivate;

enum class ConfigType {
    Json,
    Xml,
    Ini
};

/**
 * @brief The System class
 *
 * @author Sascha Häusler<saeschdivara@gmail.com>
 * @since 0.1
 */
class PUBLICSERVERSYSTEMSHARED_EXPORT System : public QObject
{
        Q_OBJECT
    public:
        System(QCoreApplication * app);
        virtual ~System();

        virtual void beforeStartUp() {}
        int startUp();
        virtual void beforeShutdown() {}

        void addServer(ServerInterface * server);

        void searchConfig(QStringList searchPaths, ConfigType type = ConfigType::Json);

    protected:
        System(SystemPrivate * pri, QCoreApplication * app);
        SystemPrivate * d_ptr;

    private:
        Q_DECLARE_PRIVATE(System)
};

}
}

#endif // SYSTEM_H
