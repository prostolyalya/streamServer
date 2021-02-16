#include "client_manager.h"
#include "thread_pool.h"
ClientManager::ClientManager(std::shared_ptr<UiController> ui, QObject *parent)
    : QObject(parent)
    , uiController(ui)
{
    connect(uiController.get(), &UiController::sendTextAllUsers, this,
            &ClientManager::sendMessageToClients, Qt::QueuedConnection);
    DB = std::make_shared<DBConnector>("clients", this);
    auth = std::make_shared<Authenticator>(DB);
}

void ClientManager::createClient(QTcpSocket *socketClient, QTcpSocket *socketSender,
                                 QTcpSocket *socketReceiver, QString login)
{
    auto client =
        std::make_unique<Client>(*socketClient, *socketSender, *socketReceiver, login);
    connect(this, &ClientManager::sendMessageToAll, client.get(), &Client::sendMessage,
            Qt::QueuedConnection);
    connect(client.get(), &Client::clientDisconnect, this,
            &ClientManager::clientDisconnected, Qt::QueuedConnection);
    connect(client.get(), &Client::messageReceived, uiController.get(),
            &UiController::addText, Qt::QueuedConnection);
    connect(uiController.get(), &UiController::sendFile, client.get(), &Client::sendFile,
            Qt::QueuedConnection);
    connect(client.get(), &Client::addFileToDB, DB.get(), &DBConnector::addFile,
            Qt::QueuedConnection);
    connect(client.get(), &Client::requestPubFiles, DB.get(),
            &DBConnector::requestPubFiles, Qt::QueuedConnection);
    connect(DB.get(), &DBConnector::responsePubFiles, client.get(),
            &Client::requestFileList, Qt::QueuedConnection);
    ThreadPool::getInstance()->addToThread(client.get());

    clients.insert(std::make_pair(login, std::move(client)));

    uiController.get()->addText(login + " connected");
}

void ClientManager::sendMessageToClients(QString text)
{
    emit sendMessageToAll(text);
}

std::shared_ptr<Authenticator> ClientManager::getAuth()
{
    return auth;
}

void ClientManager::clientDisconnected(QString login)
{
    auto it = clients.find(login);
    it->second.reset();
    clients.erase(it);
    qDebug() << login << " disconnected";
    uiController.get()->addText(login + " disconnected");
}
