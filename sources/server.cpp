#include "server.h"
#include "cryptor.h"
#include "blowfish_crypt.h"

Server::Server(std::shared_ptr<UiController> _uiController)
    : uiController(_uiController)

{
    Utils::log("------------- Start Stream Server -------------");
    connect(uiController.get(), &UiController::login, this, &Server::login);
    connect(this, &Server::loginComplete, uiController.get(),
            &UiController::loginComplete);
    uiController->startLogin();
}

Server::~Server()
{
    Utils::log("------------- Shutdown Stream Server -------------");
}

void Server::init()
{
    threadPool = std::make_unique<ThreadPool>();
    threadPool->addToThread(this);
    clientManager = std::make_unique<ClientManager>(uiController);
    connector = std::make_unique<Connector>();

    connect(clientManager.get()->getAuth().get(), &Authenticator::loginComplete,
            connector.get(), &Connector::addLogin);
    connect(connector.get(), &Connector::addClient, clientManager.get(),
            &ClientManager::createClient, Qt::QueuedConnection);
}

void Server::login(QString login, QString password, bool reg)
{
    if (!QFile().exists("profile") && !reg)
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
        QFile file2("profile");
        file2.open(QIODevice::WriteOnly);
        QByteArray data = login.toUtf8() + password.toUtf8() + "streamServer";
        data = BlowFish::encrypt(data, login.toUtf8() + password.toUtf8());
        file2.write(data);
        file2.close();
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
