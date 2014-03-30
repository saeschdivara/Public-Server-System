#include "DateField.h"

#include "AbstractFormField_p.h"

#include "widget/DateInput.h"

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{

class DateFieldPrivate : public AbstractFormFieldPrivate
{
    public:
};

DateField::DateField(const QString &name, const QString &description, QObject *parent) :
    AbstractFormField(new DateFieldPrivate, name, description, parent)
{
    Q_D(DateField);

    d->widget = new Widget::DateInput;
}

QString DateField::toString() const
{
    Q_D(const DateField);

    return d->widget->toString(d->fieldName, d->fieldValue);
}

bool DateField::hasFile() const
{
    return false;
}

}
}
}
