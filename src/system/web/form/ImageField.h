#ifndef IMAGEFIELD_H
#define IMAGEFIELD_H

#include "AbstractFormField.h"

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{

class ImageFieldPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT ImageField : public AbstractFormField
{
        Q_OBJECT
    public:
        Q_INVOKABLE explicit ImageField(const QString & name, const QString & description, QObject *parent = 0);

        virtual QString toString() const;
        virtual bool hasFile() const;

    private:
        Q_DECLARE_PRIVATE(ImageField)
};

}
}
}

#endif // IMAGEFIELD_H
