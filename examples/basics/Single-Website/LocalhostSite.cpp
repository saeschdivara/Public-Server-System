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

#include "LocalhostSite.h"

#include <system/web/AbstractSite_p.h>

#include <lib/engine.h>
#include <lib/template.h>

class IndexView : public PublicServerSystem::Web::View::ViewInterface
{
        // ViewInterface interface
    public:
        virtual void render(Grantlee::Engine * templateEngine, QTextStream &stream) {
            Q_UNUSED(templateEngine);
            stream << QStringLiteral("<html><head><meta charset=\"utf-8\"> </head><body><h1>HäLOO</h1></body></html>");
        }
};

class TestView : public PublicServerSystem::Web::View::ViewInterface
{
        // ViewInterface interface
    public:
        virtual void render(Grantlee::Engine * templateEngine, QTextStream &stream) {
        }
};

LocalhostSite::LocalhostSite(QObject *parent) :
    PublicServerSystem::Web::AbstractSite(parent)
{
    addView("/index", new IndexView);
    addView("^/", new TestView);
}