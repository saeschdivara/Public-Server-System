#include <QCoreApplication>

#include <system/core/ConnectedSystemNode.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    PublicServerSystem::Core::ConnectedSystemNode sys(&app);

    sys.startUp();

    return app.exec();
}
