#include "starter.h"

Starter::Starter(QQmlApplicationEngine &engine)
    : engine(engine)
{
}

void Starter::startServer(QString username, QString password)
{
    if (Server::checkLogin(username, password))
    {
        server = std::make_unique<Server>();
        engine.rootContext()->setContextProperty("uiController",
                                                 server.get()->getUiController().get());
        const QUrl url(QStringLiteral("qrc:/include/ui/mainServerWindow.qml"));
        engine.load(url);
    }
}

void Starter::startClient(QString username, QString password)
{
    client = std::make_unique<StreamClient>();
    engine.rootContext()->setContextProperty("uiController",
                                             client.get()->getUiController().get());
    const QUrl url(QStringLiteral("qrc:/include/ui/mainClientWindow.qml"));
    engine.load(url);
}
