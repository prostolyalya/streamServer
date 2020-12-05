#include "client_manager.h"

ClientManager::ClientManager(std::shared_ptr<UiController> ui, QObject *parent)
    : QObject(parent),
      uiController(ui)
{
    connect(uiController.get(), &UiController::sendTextAllUsers, this, &ClientManager::sendMessageToClients);
    DB = std::make_unique<DBConnector>("clients");
}

void ClientManager::createClient(QTcpSocket& socketClient, QTcpSocket &socketSender, QTcpSocket &socketReceiver)
{
//    check log/pass
    auto client = std::make_unique<Client>(socketClient, socketSender, socketReceiver, count_clients);
    connect(client.get(), &Client::clientDisconnect, this, &ClientManager::clientDisconnected);
    connect(client.get(), &Client::messageReceived, this, &ClientManager::receiveMessage);
    connect(uiController.get(), &UiController::sendFile, client.get(), &Client::sendFile);
    clients.insert(std::make_pair(count_clients, std::move(client)));
    QString num = QString::number(count_clients);
    uiController.get()->addText(num + " client connected");
    DB->addUser(num, num + " login", num + " password");
    count_clients++;
}

void ClientManager::sendMessageToClients(QString text)
{
    for(auto&client:clients)
    {
        client.second->sendMessage(text);
    }
}

void ClientManager::clientDisconnected(int id)
{
    auto it = clients.find(id);
    it->second.reset();
    clients.erase(it);
    qDebug() << id << "client disconnected";
    uiController.get()->addText(QString::number(id) + " client disconnected");
}

void ClientManager::receiveMessage(QByteArray msg)
{
    uiController.get()->addText(msg);
}


