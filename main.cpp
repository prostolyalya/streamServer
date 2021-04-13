#include <QGuiApplication>
#include <QObject>
#include <QDebug>
#include "server.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto uiController = std::make_shared<UiController>();
    auto server = std::make_unique<Server>(uiController);

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
