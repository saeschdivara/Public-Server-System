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

#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "public_server_system_globals.h"

#include "system/web/model/AbstractModel.h"

#include <Arangodbdriver.h>

namespace PublicServerSystem
{
namespace Web
{
namespace Model
{

class ModelManagerPrivate;

typedef QList<AbstractModel *> ModelList;

class PUBLICSERVERSYSTEMSHARED_EXPORT ModelManager : public QObject
{
        Q_OBJECT
    public:
        explicit ModelManager(QObject *parent = 0);

        ModelList all();

    protected:
        ModelManagerPrivate * d_ptr;
        ModelManager(ModelManagerPrivate * ptr, QObject *parent = 0);

    private:
        Q_DECLARE_PRIVATE(ModelManager)
};

arangodb::Arangodbdriver * getArangoDriver();

}
}
}

#endif // MODELMANAGER_H
