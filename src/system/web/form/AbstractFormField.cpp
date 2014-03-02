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

#include "AbstractFormField.h"
#include "AbstractFormField_p.h"

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{

int getAbstractFormFieldMetaID()
{
    return qRegisterMetaType<AbstractFormField *>("AbstractFormFieldMetaIDPtr");
}

AbstractFormField::AbstractFormField(const QString &name, const QString &description, QObject *parent) :
    AbstractFormField(new AbstractFormFieldPrivate, name, description, parent)
{
}

AbstractFormField::~AbstractFormField()
{
    delete d_ptr;
}

bool AbstractFormField::isValid() const
{
    return this->validate();
}

QVariant AbstractFormField::value() const
{
    Q_D(const AbstractFormField);

    return d->fieldValue;
}

void AbstractFormField::setValue(QVariant val)
{
    Q_D(AbstractFormField);
    d->fieldValue = val;
}

QString AbstractFormField::description() const
{
    Q_D(const AbstractFormField);
    return d->description;
}

Widget::WidgetInterface *AbstractFormField::widget() const
{
    Q_D(const AbstractFormField);

    return d->widget;
}

AbstractFormField::AbstractFormField(AbstractFormFieldPrivate *ptr, const QString & name, const QString & description, QObject *parent) :
    QObject(parent),
    d_ptr(ptr)
{
    ptr->fieldName = name;
    ptr->description = description;
}

bool AbstractFormField::validate() const
{
    return true;
}

}
}
}
