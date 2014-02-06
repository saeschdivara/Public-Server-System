#include "Mail.h"

namespace PublicServerSystem
{
namespace Email
{

class MailPrivate
{
    public:
};

Mail::Mail() :
    d_ptr(new MailPrivate)
{
}

}
}
