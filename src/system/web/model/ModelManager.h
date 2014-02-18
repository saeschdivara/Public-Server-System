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
#include "ModelManager_p.h"

#include "system/web/model/AbstractModel.h"

#include <ArangoDBDriver.h>
#include <Document.h>
#include <QueryBuilder.h>

namespace PublicServerSystem
{
namespace Web
{
namespace Model
{

class ModelManagerPrivate;

template <class T>
class PUBLICSERVERSYSTEMSHARED_EXPORT ModelManager
{
    public:
        explicit ModelManager();
        virtual ~ModelManager();

        typedef QList<T *> ModelList;

        ModelList all();
        ModelList getPart(int start, int limit);
        T * get(const QString & id);
        ModelList getByExample(const QString & exampleKey, QVariant exampleValue);
        ModelList getByExample(QVariantMap example);

        T * create();

        static arangodb::ArangoDBDriver * getArangoDriver();

    protected:
        ModelManagerPrivate * d_ptr;
        ModelManager(ModelManagerPrivate * ptr);

        arangodb::QueryBuilder * builder();

    private:
        Q_DECLARE_PRIVATE(ModelManager)
};

#define PU_DECLARE_MANAGER(Class) \
    static PublicServerSystem::Web::Model::ModelManager<Class> * objects

#define PU_DEFINE_MANAGER(Class) \
    Q_GLOBAL_STATIC(PublicServerSystem::Web::Model::ModelManager<Class>, g##Class) \
    \
    PublicServerSystem::Web::Model::ModelManager<Class> * Class::objects = g##Class();


template <class T>
ModelManager<T>::ModelManager() :
    ModelManager(new ModelManagerPrivate)
{
    //
}

template <class T>
ModelManager<T>::~ModelManager()
{
    delete d_ptr;
}

template <class T>
ModelManager<T>::ModelManager(ModelManagerPrivate *ptr) :
    d_ptr(ptr)
{
    //
}

template <class T>
typename ModelManager<T>::ModelList ModelManager<T>::all()
{
    auto driver = getArangoDriver();
    auto select = builder()->createGetAllSelect(T::staticMetaObject.className());

    auto cursor = driver->executeSelect(select);
    cursor->waitForResult();

    ModelManager::ModelList resultList;
    auto dataList = cursor->data();
    for ( arangodb::Document * dataDoc : dataList ) {
            dataDoc->sync();
            dataDoc->waitForResult();
            resultList << new T(dataDoc, 0);
        }

    return resultList;
}

template <class T>
typename ModelManager<T>::ModelList ModelManager<T>::getPart(int start, int limit)
{
    auto driver = getArangoDriver();
    auto select = builder()->createGetAllSelect(T::staticMetaObject.className());

    select->setSkipNumber(start);
    select->setLimit(limit);

    auto cursor = driver->executeSelect(select);
    cursor->waitForResult();

    ModelManager::ModelList resultList;
    auto dataList = cursor->data();
    for ( arangodb::Document * dataDoc : dataList ) {
            dataDoc->sync();
            dataDoc->waitForResult();
            resultList << new T(dataDoc, 0);
        }

    return resultList;
}

template <class T>
T * ModelManager<T>::get(const QString &id)
{
    QString realID(T::staticMetaObject.className());
    realID += QLatin1Char('/') + id;

    arangodb::Document * modelDoc = getArangoDriver()->getDocument(realID);
    modelDoc->sync();
    modelDoc->waitForResult();
    T * model = new T(modelDoc, 0);

    return model;
}

template <class T>
typename ModelManager<T>::ModelList ModelManager<T>::getByExample(const QString &exampleKey, QVariant exampleValue)
{
    QJsonObject obj;
    obj.insert(exampleKey, QJsonValue::fromVariant(exampleValue));

    auto select = builder()->createByExampleSelect(T::staticMetaObject.className(), obj);

    auto driver = getArangoDriver();
    auto cursor = driver->executeSelect(select);
    cursor->waitForResult();

    ModelManager::ModelList resultList;
    auto dataList = cursor->data();
    for ( arangodb::Document * dataDoc : dataList ) {
            dataDoc->sync();
            dataDoc->waitForResult();
            resultList << new T(dataDoc, 0);
        }

    return resultList;
}

template <class T>
typename ModelManager<T>::ModelList ModelManager<T>::getByExample(QVariantMap example)
{
    Q_UNUSED(example)
}

template <class T>
T *ModelManager<T>::create()
{
    arangodb::Document * modelDoc = getArangoDriver()->createDocument(T::staticMetaObject.className());
    T * model = new T(modelDoc, 0);

    return model;
}

template <class T>
arangodb::QueryBuilder *ModelManager<T>::builder()
{
    Q_D(ModelManager);
    return &d->qb;
}

Q_GLOBAL_STATIC(arangodb::ArangoDBDriver, gGetDriver)

template <class T>
arangodb::ArangoDBDriver *ModelManager<T>::getArangoDriver()
{
    return gGetDriver();
}

}
}
}

#endif // MODELMANAGER_H
