#include "ViewInterface.h"

#include <QtCore/QDebug>

void PublicServerSystem::Web::View::render(const QString &templateName, QTextStream &stream, Grantlee::Engine *templateEngine, Grantlee::Context *requestContext)
{
   Grantlee::OutputStream out(&stream);

   Grantlee::Template tem = templateEngine->loadByName(templateName);

   if ( tem->error() != Grantlee::NoError ) {
       qDebug() << tem->errorString();
   }

   tem->render(&out, requestContext);
}
