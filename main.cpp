#include <QGuiApplication>
#include <qqml.h>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //    qmlRegisterType<UiController>("com.server", 1, 0, "UiController");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto uiController = std::make_shared<UiController>();
    auto server = std::make_unique<Server>(uiController, engine);
    engine.rootContext()->setContextProperty("uiController",
                                             uiController.get());
    const QUrl url(QStringLiteral("qrc:/include/ui/startWindow.qml"));
    engine.load(url);

    return app.exec();
}

// const QUrl url(QStringLiteral("qrc:/include/ui/startWindow.qml"));

// QFile file("bigimage.jpg");

// if (file.open(QIODevice::ReadOnly))
//{
//    QByteArray fileData = file.readAll();

//    QByteArray hashData = QCryptographicHash::hash(fileData,QCryptographicHash::Md5); // or
//    QCryptographicHash::Sha1 qDebug() << hashData.toHex();  // 0e0c2180dfd784dd84423b00af86e2fc

//}
