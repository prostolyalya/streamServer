#include "server.h"
#include "cryptor.h"
#include "blowfish_crypt.h"

Server::Server(std::shared_ptr<UiController> _uiController,
               QQmlApplicationEngine& _engine)
    : engine(_engine)
    , uiController(_uiController)

{
    connect(uiController.get(), &UiController::login, this, &Server::login);
    connect(this, &Server::loginComplete, uiController.get(), &UiController::loginComplete);
}

void Server::init()
{
    engine.load(QStringLiteral("qrc:/include/ui/mainServerWindow.qml"));
    threadPool = std::make_unique<ThreadPool>();
    clientManager = std::make_shared<ClientManager>(uiController);
    connector = std::make_unique<Connector>(clientManager);

    connect(clientManager.get()->getAuth().get(), &Authenticator::loginComplete,
            connector.get(), &Connector::addLogin);
}

void Server::login(QString login, QString password, bool reg)
{
    if(!QFile().exists("profile") && !reg)
    {
        emit loginComplete(false);
        return;
    }
    QFile file("profile");
    if (reg)
    {
        if (QFile().exists("profile"))
        {
            QFile().remove("profile");
        }
        QFile file("profile");
        file.open(QIODevice::WriteOnly);
        QByteArray data = login.toUtf8() + password.toUtf8() + "streamServer";
        data = BlowFish::encrypt(data, login.toUtf8() + password.toUtf8());
        file.write(data);
        file.close();
        emit loginComplete(true);
        init();
        return;
    }
    else if (file.open(QIODevice::ReadWrite))
    {
        QByteArray data = file.readAll();
        if (BlowFish::decrypt(data, login.toUtf8() + password.toUtf8())
            == (login + password + "streamServer"))
        {
            emit loginComplete(true);
            init();
            file.close();
            return;
        }

    }
    emit loginComplete(false);
}
