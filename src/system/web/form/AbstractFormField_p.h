#ifndef ABSTRACTFORMFIELD_P_H
#define ABSTRACTFORMFIELD_P_H

#include "widget/WidgetInterface.h"

#include <QtCore/QVariant>

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{

class AbstractFormFieldPrivate
{
    public:
        QVariant fieldValue;
        QString fieldName;
        QString description;

        Widget::WidgetInterface * widget;
};

}
}
}

#endif // ABSTRACTFORMFIELD_P_H
