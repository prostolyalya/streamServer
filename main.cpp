#include <QGuiApplication>

#include "starter.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //    qmlRegisterType<UiController>("com.server", 1, 0, "UiController");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    auto st = std::make_unique<Starter>(engine);
    engine.rootContext()->setContextProperty("Starter", st.get());
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
