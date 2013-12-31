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

#include "AbstractSite.h"
#include "AbstractSite_p.h"

#include "system/core/Exception.h"

namespace PublicServerSystem
{
namespace Web
{

AbstractSite::AbstractSite(QObject *parent) :
    QObject(parent),
    d_ptr(new AbstractSitePrivate)
{
    d_ptr->engine = new Grantlee::Engine(this);
}

AbstractSite::~AbstractSite()
{
    qDeleteAll(d_ptr->views);

    delete d_ptr;
}

void AbstractSite::addView(const QString &urlRegex, View::ViewInterface *view)
{
    Q_D(AbstractSite);
    d->views.insert(urlRegex, view);
}

View::ViewInterface *AbstractSite::view(const QString &urlPath) const
{
    Q_D(const AbstractSite);
    for ( auto urlRegex : d->views.keys() ) {
            QRegularExpression regex(urlRegex);
            QRegularExpressionMatch match = regex.match(urlPath);
            bool hasMatch = match.hasMatch(); // true
            if ( hasMatch ) {
                    return d->views.value(urlRegex);
                }
        }

    throw Core::Exception(Core::ErrorCode::NotFound, QStringLiteral("Not found"));
}

Grantlee::Engine *AbstractSite::templateEngine() const
{
    Q_D(const AbstractSite);
    return d->engine;
}

}
}
