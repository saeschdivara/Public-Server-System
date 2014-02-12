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

#ifndef MODELFORM_H
#define MODELFORM_H

#include "public_server_system_globals.h"

#include "AbstractFormField.h"

#include <QtCore/QMetaProperty>

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{

template <class T>
class PUBLICSERVERSYSTEMSHARED_EXPORT ModelForm
{
    public:
        ModelForm(T * model);

        QList<AbstractFormField *> getAllFields() const;

        QString toString() const;

    protected:
        T * m_model;
};

template <class T>
ModelForm<T>::ModelForm(T *model) :
    m_model(model)
{
}

template <class T>
QList<AbstractFormField *> ModelForm<T>::getAllFields() const
{
    const QMetaObject metaObj = T::staticMetaObject;
    int start = metaObj.propertyOffset();
    int count = metaObj.propertyCount();

    int fieldMetaID = getAbstractFormFieldMetaID();

    QList<AbstractFormField *> fields;

    for (int i = start; i < count; ++i) {
        QMetaProperty prop = metaObj.property(i);
        QVariant propValue = prop.read(m_model);
        if (propValue.canConvert(fieldMetaID)) {
            AbstractFormField * field = propValue.value<AbstractFormField *>();
            fields.append(field);
        }
    }

    return fields;
}

template <class T>
QString ModelForm<T>::toString() const
{
    QString output;
    QList<AbstractFormField *> fields = getAllFields();

    output += "<form method=\"POST\">";

    for ( AbstractFormField * field : fields ) {
        output += "<div class=\"widget\">";
        output += "<label>" + field->description() + "</label>";
        output += field->widget()->toString(field->value());
        output += "</div>";
    }

    output += "<input type=\"submit\" />";
    output += "</form>";

    return output;
}

}
}
}

#endif // MODELFORM_H
