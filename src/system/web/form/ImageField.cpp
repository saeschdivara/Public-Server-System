#include "ImageField.h"

#include "AbstractFormField_p.h"

#include "widget/FileInput.h"

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{

class ImageFieldPrivate : public AbstractFormFieldPrivate
{
    public:
};

ImageField::ImageField(const QString &name, const QString &description, QObject *parent) :
    AbstractFormField(new ImageFieldPrivate, name, description, parent)
{
    Q_D(ImageField);

    d->widget = new Widget::FileInput;
}

QString ImageField::toString() const
{
    Q_D(const ImageField);

    return d->widget->toString(d->fieldName, d->fieldValue);
}

bool ImageField::hasFile() const
{
    return true;
}

}
}
}
