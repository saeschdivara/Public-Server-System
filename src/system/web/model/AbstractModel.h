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

#ifndef ABSTRACTMODEL_H
#define ABSTRACTMODEL_H

#include "public_server_system_globals.h"
#include "system/web/form/AbstractFormField.h"

#include <Document.h>

#include <QtCore/QMetaObject>
#include <QtCore/QVariant>

namespace PublicServerSystem
{
namespace Web
{
namespace Model
{

class AbstractModelPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT AbstractModel : public QObject
{
        Q_OBJECT
    public:
        explicit AbstractModel(QObject *parent = 0);
        AbstractModel(arangodb::Document * doc, QObject *parent = 0);
        AbstractModel(const AbstractModel & mo);
        virtual ~AbstractModel();

        void save();

    protected:
        AbstractModel(arangodb::Document * doc, AbstractModelPrivate * ptr, QObject *parent = 0);
        AbstractModel(AbstractModelPrivate * ptr, QObject *parent = 0);
        AbstractModelPrivate * d_ptr;

        QVariant get(const QString & name) const;
        void set(const QString & name, QVariant val);

        Form::AbstractFormField * field(const QString & referencingPropertyName, const QMetaObject &fieldClassObj);

    private:
        Q_DECLARE_PRIVATE(AbstractModel)
};

}
}
}

#endif // ABSTRACTMODEL_H
