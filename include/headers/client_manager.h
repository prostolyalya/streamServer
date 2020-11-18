#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <string>
#include <QtNetwork>
#include <vector>
#include "client.h"
#include "ui_controller.h"
class ClientManager
{
public:
    ClientManager(std::shared_ptr<UiController> ui);
    void createClient(QTcpSocket &socket);
    void sendMessageToClients(QString text);
    void clientDisconnected();
private:
    std::shared_ptr<UiController> uiController;
    std::vector<std::unique_ptr<Client>> clients;
    int count_clients = 1;
};
#endif // CLIENTMANAGER_H
