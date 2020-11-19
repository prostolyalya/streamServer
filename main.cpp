#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "server.h"
#include "stream_client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterType<UiController>("com.server", 1, 0, "UiController");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // create server
//    const QUrl url(QStringLiteral("qrc:/include/ui/mainServerWindow.qml"));
//    auto server = std::make_unique<Server>();
//    engine.rootContext()->setContextProperty("uiController", server.get()->getUiController().get());
    // create client
    const QUrl url(QStringLiteral("qrc:/include/ui/mainClientWindow.qml"));
    auto client = std::make_unique<StreamClient>();
    engine.rootContext()->setContextProperty("uiController", client.get()->getUiController().get());

    engine.load(url);

    return app.exec();
}
