#ifndef DATEFIELD_H
#define DATEFIELD_H

#include "AbstractFormField.h"

namespace PublicServerSystem
{
namespace Web
{
namespace Form
{

class DateFieldPrivate;

class PUBLICSERVERSYSTEMSHARED_EXPORT DateField : public AbstractFormField
{
        Q_OBJECT
    public:
        Q_INVOKABLE explicit DateField(const QString & name, const QString & description, QObject *parent = 0);

        virtual QVariant convert(const QByteArray & value) const;
        virtual QString toString() const;
        virtual bool hasFile() const;

    private:
        Q_DECLARE_PRIVATE(DateField)
};

}
}
}

#endif // DATEFIELD_H
