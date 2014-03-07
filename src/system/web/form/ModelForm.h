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

#include <QtCore/QDebug>
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
        ModelForm(T * model, QHash<QString, QString> * post);

        QList<AbstractFormField *> getAllFields() const;

        bool isValid() const;

        void save();

        QString toString() const;

    protected:
        T * m_model;
        QHash<QString, QString> * m_post;
        QList<AbstractFormField *> m_fields;
};

template <class T>
ModelForm<T>::ModelForm(T *model, QHash<QString, QString> *post) :
    m_model(model),
    m_post(post)
{
    m_fields = getAllFields();
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

            QString propertyName = prop.name();
            QString widgetName = QString("m_%1").arg(propertyName);

            // Only if the field is in the post
            if (m_post->contains(widgetName)) {
                field->setValue(m_post->value(widgetName));
            }

            fields.append(field);
        }
    }

    return fields;
}

template <class T>
bool ModelForm<T>::isValid() const
{
    for ( AbstractFormField * field : m_fields ) {
        if ( !field->isValid() ) return false;
    }

    return true;
}


template <class T>
void ModelForm<T>::save()
{
    for ( AbstractFormField * field : m_fields ) {
        m_model->setProperty(field->name().toLatin1().data(), field->value());
    }
}

template <class T>
QString ModelForm<T>::toString() const
{
    QString output;

    output += "<form method=\"POST\" action=\".\">";
    output += QString("<input name=\"id\" type=\"hidden\" value=\"%1\" />").arg(m_model->dbCollectionKey());

    for ( AbstractFormField * field : m_fields ) {
        output += "<div class=\"widget\">";
        output += "<label>" + field->description() + "</label>";
        output += field->toString();
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
