#include "client_manager.h"
#include "thread_pool.h"
#include "utils.h"

ClientManager::ClientManager(std::shared_ptr<UiController> ui, QString _path, QString address, QObject *parent)
    : QObject(parent)
    , uiController(ui)
    , path(_path)
{
    DB = std::make_shared<DBConnector>(path + "clients", this);
    auth = std::make_shared<Authenticator>(DB, address);
}

void ClientManager::createClient(QTcpSocket *socketClient, QTcpSocket *socketSender,
                                 QTcpSocket *socketReceiver, QString login)
{
    auto client = std::make_unique<Client>(*socketClient, *socketSender, *socketReceiver, login, path);
    connect(this, &ClientManager::sendMessageToAll, client.get(), &Client::sendMessage, Qt::QueuedConnection);
    connect(client.get(), &Client::clientDisconnect, this, &ClientManager::clientDisconnected,
            Qt::QueuedConnection);
    connect(client.get(), &Client::messageReceived, uiController.get(), &UiController::addText,
            Qt::QueuedConnection);
    connect(client.get(), &Client::addFileToDB, DB.get(), &DBConnector::addFile, Qt::QueuedConnection);
    connect(client.get(), &Client::requestPubFiles, DB.get(), &DBConnector::requestPubFiles,
            Qt::QueuedConnection);
    connect(DB.get(), &DBConnector::responsePubFiles, client.get(), &Client::requestFileList,
            Qt::QueuedConnection);
    ThreadPool::getInstance()->addToThread(client.get());

    clients.insert(std::make_pair(login, std::move(client)));

    uiController.get()->addText(login + " connected");
}

QStringList ClientManager::getClients()
{
    QStringList names{};
    for (auto& p : clients)
    {
        names.append(p.first + "|" + p.second.get()->getAddress().toString());
    }
    return names;
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
    Utils::log(login + " disconnected");
}
