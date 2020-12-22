#include "client_manager.h"
#include "thread_pool.h"
ClientManager::ClientManager(std::shared_ptr<UiController> ui, QObject *parent)
    : QObject(parent)
    , uiController(ui)
{
    connect(uiController.get(), &UiController::sendTextAllUsers, this, &ClientManager::sendMessageToClients,
            Qt::QueuedConnection);
    DB = std::make_unique<DBConnector>("clients");
}

void ClientManager::createClient(QTcpSocket &socketClient, QTcpSocket &socketSender,
                                 QTcpSocket &socketReceiver)
{
    //    check log/pass
    auto client = std::make_unique<Client>(socketClient, socketSender, socketReceiver, count_clients);
    connect(this, &ClientManager::sendMessageToAll, client.get(), &Client::sendMessage, Qt::QueuedConnection);
    connect(client.get(), &Client::clientDisconnect, this, &ClientManager::clientDisconnected,
            Qt::QueuedConnection);
    connect(client.get(), &Client::messageReceived, uiController.get(), &UiController::addText,
            Qt::QueuedConnection);
    connect(uiController.get(), &UiController::sendFile, client.get(), &Client::sendFile,
            Qt::QueuedConnection);
    ThreadPool::getInstance()->addToThread(client.get());
    clients.insert(std::make_pair(count_clients, std::move(client)));
    QString num = QString::number(count_clients);
    uiController.get()->addText(num + " client connected");
    DB->addUser(num, num + " login", num + " password");
    count_clients++;
}

void ClientManager::sendMessageToClients(QString text)
{
    emit sendMessageToAll(text);
}

void ClientManager::clientDisconnected(int id)
{
    auto it = clients.find(id);
    it->second.reset();
    clients.erase(it);
    qDebug() << id << "client disconnected";
    uiController.get()->addText(QString::number(id) + " client disconnected");
}
