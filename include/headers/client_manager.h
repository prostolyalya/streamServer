#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#pragma once
#include <string>
#include <QtNetwork>
#include <vector>
#include "client.h"

class ClientManager
{
public:

    void createClient(QTcpSocket &socket);
private:

    std::vector<std::unique_ptr<Client>> clients;
};
#endif // CLIENTMANAGER_H
