#include "server.h"
#include "cryptor.h"
Server::Server(std::shared_ptr<UiController> _uiController,
               QQmlApplicationEngine& _engine)
    : engine(_engine)
    , uiController(_uiController)

{
    connect(uiController.get(), &UiController::init, this, &Server::init);
}

bool Server::checkLogin(QString username, QString password)
{
    return true;
    QFile file("path");
    if (file.open(QFile::ReadOnly))
    {
        std::string pass = username.toStdString() + password.toStdString();
        std::string readData = file.readAll().toStdString();
        std::vector<char> data;
        for (auto& symb : readData)
        {
            data.push_back(symb);
        }

        Cryptor::encryptDecrypt(pass, data);
        std::string validData(data.begin(), data.end());
        if (validData == "Validate")
        {
            // start
        }
    }

    return false;
}

void Server::init(QString login, QString pass)
{
    engine.load(QStringLiteral("qrc:/include/ui/mainServerWindow.qml"));
    threadPool = std::make_unique<ThreadPool>();
    clientManager = std::make_shared<ClientManager>(uiController);
    connector = std::make_unique<Connector>(clientManager);
}
