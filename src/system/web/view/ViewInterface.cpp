#include "ViewInterface.h"

void PublicServerSystem::Web::View::render(const QString &templateName, QTextStream &stream, Grantlee::Engine *templateEngine, Grantlee::Context *requestContext)
{
   Grantlee::OutputStream out(&stream);

   Grantlee::Template tem = templateEngine->loadByName(templateName);

   tem->render(&out, requestContext);
}
