#ifndef FILEINPUT_H
#define FILEINPUT_H

#include "WidgetInterface.h"

#include <QtCore/QVariant>

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{
namespace Widget
{

class FileInput : public WidgetInterface
{
    public:
        virtual QString toString(const QString & name, const QVariant & value) const {
            return QString("<input type=\"file\" name=\"m_%1_field\" />").arg(name);
        }
};

}
}
}
}

#endif // FILEINPUT_H
