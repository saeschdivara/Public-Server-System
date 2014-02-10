#include <system/core/ConnectedSystemNode.h>
#include <system/email/SmtpServer.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    PublicServerSystem::Core::ConnectedSystemNode node(&app);

    PublicServerSystem::Email::SmtpServer smtpServer;
    smtpServer.listen(QHostAddress::Any, 8999);

    node.addServer(&smtpServer);

    return node.startUp();
}
