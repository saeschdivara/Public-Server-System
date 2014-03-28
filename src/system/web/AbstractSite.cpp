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

#include <QtCore/QDebug>

namespace PublicServerSystem
{
namespace Web
{

AbstractSite::AbstractSite(QObject *parent) :
    AbstractSite(new AbstractSitePrivate, parent)
{
}

AbstractSite::AbstractSite(AbstractSitePrivate *pri, QObject *parent) :
    QObject(parent),
    d_ptr(pri)
{
    pri->engine = new Grantlee::Engine(this);
}

AbstractSite::~AbstractSite()
{
    const int total = d_ptr->views.length();
    for (int i = 0; i < total; ++i) {
        delete d_ptr->views.at(i).second;
    }

    delete d_ptr;
}

void AbstractSite::addView(const QString &urlRegex, View::ViewInterface *view)
{
    Q_D(AbstractSite);
    d->views.append(qMakePair<QString, View::ViewInterface *>(urlRegex, view));
}

int AbstractSite::findView(const QString &urlPath) const
{
    Q_D(const AbstractSite);
    int i = 0;
    for( QPair<QString, View::ViewInterface *> pair : d->views ) {
        QString urlRegex = pair.first;

        QRegularExpression regex(urlRegex);
        QRegularExpressionMatch match = regex.match(urlPath);
        bool hasMatch = match.hasMatch(); // true
        if ( hasMatch ) {
            return  i;
        }

        i++;
    }

    throw Core::Exception(Core::ErrorCode::NotFound, QStringLiteral("Not found"));
}

QHash<QString, QString> AbstractSite::urlParameters(const int index, const QString &urlPath) const
{
    Q_D(const AbstractSite);
    QPair<QString, View::ViewInterface *> pair = d->views.at(index);
    QString urlRegex = pair.first;

    QRegularExpression regex(urlRegex);
    QRegularExpressionMatch match = regex.match(urlPath);

    QHash<QString, QString> parameters;

    if ( match.hasMatch() ) {
        const int total = match.lastCapturedIndex();
        const QStringList capturedNames =  match.capturedTexts();

        for (int i = 0; i < total; ++i) {
            QString nameCaptured = capturedNames.at(i);
            QString valueCaptured = match.captured(i);

            parameters.insert(nameCaptured, valueCaptured);
        }
    }

    return parameters;
}

View::ViewInterface *AbstractSite::view(const int index) const
{
    Q_D(const AbstractSite);
    QPair<QString, View::ViewInterface *> pair = d->views.at(index);
    return pair.second;
}

Grantlee::Engine *AbstractSite::templateEngine() const
{
    Q_D(const AbstractSite);
    return d->engine;
}

}
}
