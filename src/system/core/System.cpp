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

#include "System.h"

#include <QtCore/QDebug>

namespace PublicServerSystem
{
namespace Core
{

class SystemPrivate
{
    public:
        QCoreApplication *app;
};

System::System(QCoreApplication *app) :
    d_ptr(new SystemPrivate)
{
    d_ptr->app = app;
}

System::~System()
{
    delete d_ptr;
}

int System::startUp()
{
    Q_D(System);
    int returnCode = 0; // everything worked out as expected

    try {
        d->app->exec();
    } catch (...) {
        qWarning() << Q_FUNC_INFO << "Something went terrible wrong!";
    }

    return returnCode;
}

void System::addServer(ServerInterface *server)
{
    Q_UNUSED(server)
}

}
}