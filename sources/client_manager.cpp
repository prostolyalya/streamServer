#include "client_manager.h"

void ClientManager::createClient(QTcpSocket& socket)
{
    clients.push_back(std::make_unique<Client>(socket));
}
