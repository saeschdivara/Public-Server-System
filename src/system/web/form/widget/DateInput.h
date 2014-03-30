#ifndef DATEINPUT_H
#define DATEINPUT_H

#include "WidgetInterface.h"

#include <QtCore/QString>
#include <QtCore/QVariant>

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{
namespace Widget
{

class PUBLICSERVERSYSTEMSHARED_EXPORT DateInput : public WidgetInterface
{
    public:
        virtual QString toString(const QString & name, const QVariant & value) const {
            return QString("<input type=\"text\" name=\"m_%1_field\" value=\"%2\" />").arg(name, value.toString());
        }
};

}
}
}
}

#endif // DATEINPUT_H
