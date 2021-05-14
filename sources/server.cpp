#include "server.h"
#include "cryptor.h"
#include "blowfish_crypt.h"

Server::Server(std::shared_ptr<UiController> _uiController, Utils::startParameters param)
    : filePath(!param.folder.isEmpty() ? param.folder :QDir::currentPath() + "/data/")
    , address(param.address_port)
    , uiController(_uiController)

{
    if (!param.log_file.isEmpty())
    {
        Utils::logFile = param.log_file;
        Utils::log( "Log file name was set to " + param.log_file);
    }
    if (!param.address_port.isEmpty())
    {
        Utils::log("Server address was set to " + param.address_port);
    }
    if (!param.folder.isEmpty())
    {
        Utils::log("Server folder was set to " + param.folder);
    }
    if (!param.login.isEmpty())
    {
        Utils::log("Login was set to " + param.login);
    }
    if (!param.password.isEmpty())
    {
        Utils::log("Password was set");
    }
    Utils::log("------------- Start Stream Server -------------");
    QDir().mkdir(filePath);
    connect(uiController.get(), &UiController::login, this, &Server::login);
    connect(this, &Server::loginComplete, uiController.get(), &UiController::loginComplete);
    uiController->startLogin(filePath, param.login, param.password);
}

void Server::init()
{
    clientManager = std::make_unique<ClientManager>(uiController, filePath, address);
    connector = std::make_unique<Connector>(address);

    connect(clientManager.get()->getAuth().get(), &Authenticator::loginComplete, connector.get(),
            &Connector::addLogin);
    connect(connector.get(), &Connector::addClient, clientManager.get(), &ClientManager::createClient,
            Qt::QueuedConnection);
    Utils::log("Stream Server initialized");
    QStringList names = {};
    Utils::loadWhiteList(names, filePath);
    for (auto& name : names)
    {
        QStringList par = name.split("|");
        QHostAddress address(par.at(1));
        QString log = par.at(0);
        connector->addLogin(address, log);
    }
    ThreadPool::getInstance()->addToThread(this);
    QTimer::singleShot(1000, this, &Server::checkInput);
}

void Server::login(QString login, QString password, bool reg)
{
    QString fileProfile(filePath + "profile");
    if (!QFile().exists(fileProfile) && !reg)
    {
        emit loginComplete(false, filePath);
        return;
    }
    QFile file(fileProfile);
    if (reg)
    {
        if (QFile().exists(fileProfile))
        {
            QFile().remove(fileProfile);
        }
        QFile file2(fileProfile);
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
    emit loginComplete(false, filePath);
}

void Server::checkInput()
{
    bool ex = true;
    while (ex)
    {
        QString something;
        QTextStream cin(stdin);
        while (something.isEmpty())
            cin >> something;
        if (something == "wipe")
        {
            Utils::wipe(filePath);
            Utils::log("------------- Shutdown Stream Server -------------");
            ex = !ex;
            qApp->quit();
        }
        else if (something == "exit")
        {
            Utils::saveWhiteList(clientManager->getClients(), filePath);
            Utils::log("------------- Shutdown Stream Server -------------");
            ex = !ex;
            qApp->quit();
        }
        else
        {
            Utils::log("Incorrect input: " + something);
            something.clear();
        }
    }
}
