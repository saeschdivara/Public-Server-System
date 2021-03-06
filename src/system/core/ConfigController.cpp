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

#include "ConfigController.h"

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QStringList>

namespace PublicServerSystem
{
namespace Core
{

class ConfigControllerPrivate
{
    public:
        QFile * file = Q_NULLPTR;
};

ConfigController::ConfigController(QObject *parent) :
    QObject(parent),
    d_ptr(new ConfigControllerPrivate)
{
}

bool ConfigController::searchJsonConfig(const QStringList &searchPaths)
{
    for ( auto path : searchPaths ) {
            if (searchJsonConfig(path)) {
                    return true;
                }
        }

    return false;
}

bool ConfigController::searchJsonConfig(const QString &searchPath)
{
    Q_D(ConfigController);

    QString filePath;

    if (!searchPath.endsWith("/")) {
            filePath = searchPath + QLatin1Char('/') + "config.json";
        }
    else {
            filePath = searchPath + "config.json";
        }
    QFile * file = new QFile(filePath);

    if (!file->open(QIODevice::ReadWrite)) {
            delete file;
            return false;
        }

    d->file = file;
    return true;
}

void ConfigController::discard()
{
    Q_D(ConfigController);

    if (d->file) {
            if (d->file->isOpen()) {
                    d->file->close();
                }

            delete d->file;
        }
}

}
}
