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

#ifndef VIEWINTERFACE_H
#define VIEWINTERFACE_H

#include "public_server_system_globals.h"
#include "system/web/UserSession.h"

// Grantlee
#include <lib/engine.h>
// Qt
#include <QtCore/QTextStream>
#include <QtWebRequest.h>

namespace PublicServerSystem
{
namespace Web
{
namespace View
{

class PUBLICSERVERSYSTEMSHARED_EXPORT ViewInterface
{
    public:
        virtual ~ViewInterface() {}

        virtual void render(QTextStream & stream,
                            Grantlee::Engine * templateEngine,
                            Grantlee::Context * requestContext,
                            QtWebRequest * request) = 0;
};

void render(const QString & templateName,
            QTextStream & stream,
            Grantlee::Engine * templateEngine,
            Grantlee::Context * requestContext);

}
}
}

#endif // VIEWINTERFACE_H
