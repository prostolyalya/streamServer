#include <QCoreApplication>
#include <QObject>
#include "server.h"

int main(int argc, char *argv[])
{
    Utils::startParameters param;
    if (Utils::checkOptions(argc, argv, param))
    {
        return 0;
    }
    QCoreApplication app(argc, argv);

    auto uiController = std::make_shared<UiController>();
    auto server = std::make_unique<Server>(uiController, param);

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
