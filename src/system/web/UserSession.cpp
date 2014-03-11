#include "UserSession.h"

#include <headers.h>
#include <url.h>

#include <QtCore/QDebug>
#include <QtCore/QUrlQuery>

namespace PublicServerSystem
{
namespace Web
{

UserSession::UserSession(Tufao::HttpServerRequest *request, Tufao::HttpServerResponse *response)
{
    Tufao::Url url(Tufao::Url::url(request));
    Tufao::Headers headers = request->headers();

    QUrlQuery query(url.query());
    this->m_get = query.queryItems();

    QByteArray contentType = headers.value("Content-Type");
    QList<QByteArray> splittedContentType = contentType.split(';');

    if ( splittedContentType.first() != "multipart/form-data" ) {
        QByteArray requestBody = request->body().replace('+', "%20");
        QString bodyString = requestBody;
        QUrlQuery postQuery(bodyString);
        for ( QPair<QString, QString> itemPair : postQuery.queryItems(QUrl::PrettyDecoded) ) {
            QString key = itemPair.first;
            QString value = itemPair.second;

            this->m_post.insert(key, value);
        }
    }
    else {
        QByteArray boundarySearchString(" boundary=");
        QByteArray boundaryPart = splittedContentType.at(1);
        auto indexOfBoundary = boundaryPart.indexOf(boundarySearchString);
        if ( indexOfBoundary == -1 ) return;
        QByteArray boundary = boundaryPart.remove(indexOfBoundary, boundarySearchString.length());

        QByteArray start_end("--");
        QByteArray line_break("\r\n");
        QByteArray contentDisposition("Content-Disposition: ");
        QByteArray contentType("Content-Type: ");
        QByteArray name(" name=");
        QByteArray fileName(" filename=");

        qDebug() << request->responseOptions();
        QByteArray bodyData = request->body();

        Q_FOREVER {
            auto indexOfStart = bodyData.indexOf(start_end);
            if ( indexOfStart == -1 ) break;
            bodyData = bodyData.remove(indexOfStart, start_end.length());

            auto indexOfBoundary = bodyData.indexOf(boundary);
            if ( indexOfBoundary == -1 ) break;
            bodyData = bodyData.remove(indexOfBoundary, boundary.length());

            auto indexOfBreak = bodyData.indexOf(line_break);
            if ( indexOfBreak == -1 ) break;
            bodyData = bodyData.remove(indexOfBreak, line_break.length());

            auto indexOfContentDisposition = bodyData.indexOf(contentDisposition);
            if ( indexOfContentDisposition == -1 ) break;
            bodyData = bodyData.remove(indexOfContentDisposition, contentDisposition.length());

            indexOfBreak = bodyData.indexOf(line_break);
            QByteArray contentDispositionLine = bodyData.left(indexOfBreak);
            QList<QByteArray> splittedDisposition = contentDispositionLine.split(';');
            bodyData = bodyData.remove(0, indexOfBreak + line_break.length());

            QByteArray namePart = splittedDisposition.at(1);

            auto indexOfName = namePart.indexOf(name);
            if ( indexOfName == -1 ) break;
            namePart = namePart.remove(indexOfName, name.length());

            QByteArray nameValue = namePart.left(namePart.length() -1);
            nameValue = nameValue.right(nameValue.length() -1);

            if ( splittedDisposition.size() == 2 ) {

                auto indexOfBreak = bodyData.indexOf(line_break);
                if ( indexOfBreak == -1 ) break;
                bodyData = bodyData.remove(indexOfBreak, line_break.length());

                indexOfBreak = bodyData.indexOf(line_break);
                if ( indexOfBreak == -1 ) break;
                QByteArray value = bodyData.mid(0, indexOfBreak);
                bodyData = bodyData.remove(0, indexOfBreak + line_break.length());

                QString nameString(nameValue);
                QString valueString(value);
                m_post.insert(nameString, valueString);
            }
            else {
                QByteArray fileNamePart = splittedDisposition.at(2);

                auto indexOfFileName = fileNamePart.indexOf(fileName);
                if ( indexOfFileName == -1 ) break;
                fileNamePart = fileNamePart.remove(indexOfFileName, fileName.length());

                QByteArray fileNameValue = fileNamePart.left(fileNamePart.length() -1);
                fileNameValue = fileNameValue.right(fileNameValue.length() -1);
            }
        }
    }
}

}
}
