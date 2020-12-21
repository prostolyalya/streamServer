#include "server.h"
#include "cryptor.h"
Server::Server()
{
    threadPool = std::make_unique<ThreadPool>();
    uiController = std::make_shared<UiController>();
    clientManager = std::make_shared<ClientManager>(uiController);
    connector = std::make_unique<Connector>(clientManager);
}

std::shared_ptr<UiController> Server::getUiController() const
{
    return uiController;
}

bool Server::checkLogin(QString username, QString password)
{
    return true;
    QFile file("path");
    if(file.open(QFile::ReadOnly))
    {
        std::string pass = username.toStdString() + password.toStdString();
        std::string readData = file.readAll().toStdString();
        std::vector<char> data;
        for (auto&symb : readData)
        {
            data.push_back(symb);
        }

        Cryptor::encryptDecrypt(pass, data);
        std::string validData(data.begin(), data.end());
        if (validData == "Validate")
        {
            //start
        }
    }

    return false;
}
