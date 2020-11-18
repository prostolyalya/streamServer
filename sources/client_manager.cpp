#include "client_manager.h"

ClientManager::ClientManager(std::shared_ptr<UiController> ui)
    : uiController(ui)
{
}

void ClientManager::createClient(QTcpSocket& socket)
{
//    check log/pass

    clients.push_back(std::make_unique<Client>(socket));
    uiController.get()->addTextServer(QString::number(count_clients) + " clients");
    count_clients++;
}

void ClientManager::sendMessageToClients(QString text)
{
    for(auto&client:clients)
    {
        client.get()->sendMessage(text);
    }
}

void ClientManager::clientDisconnected()
{
    qDebug() << count_clients << "client disconnected";
    uiController.get()->addTextServer("client disconnected");
    count_clients--;
}
