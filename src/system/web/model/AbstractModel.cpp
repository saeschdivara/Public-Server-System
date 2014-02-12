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

#include "AbstractModel.h"
#include "AbstractModel_p.h"

namespace PublicServerSystem
{
namespace Web
{
namespace Model
{

AbstractModel::AbstractModel(QObject *parent) :
    AbstractModel(new AbstractModelPrivate, parent)
{
}

AbstractModel::AbstractModel(arangodb::Document *doc, QObject *parent) :
    AbstractModel(doc, new AbstractModelPrivate, parent)
{
}

AbstractModel::AbstractModel(const AbstractModel &mo) :
    AbstractModel(new AbstractModelPrivate, mo.parent())
{
    Q_D(AbstractModel);
    d->doc = mo.d_ptr->doc;
}

AbstractModel::~AbstractModel()
{
    delete d_ptr;
}

AbstractModel::AbstractModel(arangodb::Document *doc, AbstractModelPrivate *ptr, QObject *parent) :
    AbstractModel(ptr, parent)
{
    Q_D(AbstractModel);
    d->doc = doc;
}

AbstractModel::AbstractModel(AbstractModelPrivate *ptr, QObject *parent) :
    QObject(parent),
    d_ptr(ptr)
{
}

QVariant AbstractModel::get(const QString &name) const
{
    Q_D(const AbstractModel);

    return d->doc->get(name);
}

void AbstractModel::set(const QString &name, QVariant val)
{
    Q_D(AbstractModel);

    d->doc->set(name, val);
}

Form::AbstractFormField *AbstractModel::field(const QString &referencingPropertyName, const QMetaObject &fieldClassObj, const QString &description)
{
    Q_D(AbstractModel);

    Form::AbstractFormField * thisField;

    // If the field has already been created
    if (d->fields.contains(referencingPropertyName)) {
            thisField = d->fields.value(referencingPropertyName);
        }
    else {
        thisField = qobject_cast<Form::AbstractFormField *>(fieldClassObj.newInstance(
                                                                Q_ARG(QObject *, 0),
                                                                Q_ARG(QString, description)
                                                            ));
        d->fields.insert(referencingPropertyName, thisField);
    }

    // Get current value for the field
    thisField->setValue(d->doc->get(referencingPropertyName));

    return thisField;
}

}
}
}
