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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "public_server_system_globals.h"

#include <httpserverresponse.h>

#include <exception>

namespace PublicServerSystem
{
namespace Core
{

enum class ErrorCode {
    NotFound
};

class PUBLICSERVERSYSTEMSHARED_EXPORT Exception : std::exception
{
    public:
        Exception(ErrorCode code, const QString & reason) Q_DECL_NOEXCEPT :
            m_code(code), m_reason(reason)
        { }

        virtual ~Exception() Q_DECL_NOEXCEPT {}

        /** Returns a C-style character string describing the general cause
         *  of the current error.  */
        virtual const char* what() const Q_DECL_NOEXCEPT {
            return m_reason.toLocal8Bit();
        }

        virtual ErrorCode code() {
            return m_code;
        }

    protected:
        ErrorCode m_code;
        QString m_reason;
};

PUBLICSERVERSYSTEMSHARED_EXPORT Tufao::HttpServerResponse::StatusCode errorCodeToStatusCode(ErrorCode code);

}
}

#endif // EXCEPTION_H
