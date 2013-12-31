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

#ifndef ABSTRACTSITE_H
#define ABSTRACTSITE_H

#include "public_server_system_globals.h"

#include "system/web/view/ViewInterface.h"

// Grantlee
#include <lib/engine.h>
// Qt
#include <QtCore/QRegularExpression>

namespace PublicServerSystem
{
namespace Web
{

class AbstractSitePrivate;

class AbstractSite : public QObject
{
        Q_OBJECT
    public:
        explicit AbstractSite(QObject *parent = 0);
        virtual ~AbstractSite();

        void addView(const QString & urlRegex, View::ViewInterface * view);
        View::ViewInterface * view(const QString & urlPath) const;

        Grantlee::Engine * templateEngine() const;

    protected:
        AbstractSitePrivate * d_ptr;

    private:
        Q_DECLARE_PRIVATE(AbstractSite)
};

}
}

#endif // ABSTRACTSITE_H