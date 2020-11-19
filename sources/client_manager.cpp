#include "client_manager.h"

ClientManager::ClientManager(std::shared_ptr<UiController> ui, QObject *parent)
    : QObject(parent),
      uiController(ui)
{
    connect(uiController.get(), &UiController::sendTextAllUsers, this, &ClientManager::sendMessageToClients);
}

void ClientManager::createClient(QTcpSocket& socket)
{
//    check log/pass
    auto client = std::make_unique<Client>(socket, count_clients);
    connect(client.get(), &Client::clientDisconnect, this, &ClientManager::clientDisconnected);
    connect(client.get(), &Client::messageReceived, this, &ClientManager::receiveMessage);
    clients.insert(std::make_pair(count_clients, std::move(client)));
    uiController.get()->addText(QString::number(count_clients) + " client connected");
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


