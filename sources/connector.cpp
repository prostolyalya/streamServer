#include "headers/connector.h"
#include <QCoreApplication>
#include <set>
Connector::Connector(std::shared_ptr<ClientManager> _clientManager, QObject *parent)
    : QObject(parent)
    , clientManager(_clientManager)
{
    serverClients = std::make_unique<QTcpServer>(this);
    serverReceiver = std::make_unique<QTcpServer>(this);
    serverSender = std::make_unique<QTcpServer>(this);
    connect(serverClients.get(), &QTcpServer::newConnection, this,
            &Connector::slotNewConnectionClient);
    connect(serverReceiver.get(), &QTcpServer::newConnection, this,
            &Connector::slotNewConnectionReceiver);
    connect(serverSender.get(), &QTcpServer::newConnection, this,
            &Connector::slotNewConnectionSender);

    if (!serverClients->listen(QHostAddress::Any, 6000))
    {
        qDebug() << "serverClients is not started";
    }
    else
    {
        qDebug() << "serverClients is started";
    }
    if (!serverReceiver->listen(QHostAddress::Any, 6001))
    {
        qDebug() << "serverReceiver is not started";
    }
    else
    {
        qDebug() << "serverReceiver is started";
    }
    if (!serverSender->listen(QHostAddress::Any, 6002))
    {
        qDebug() << "serverSender is not started";
    }
    else
    {
        qDebug() << "serverSender is started";
    }
}

void Connector::slotNewConnectionClient()
{
    auto socket = serverClients->nextPendingConnection();
    mapSockets.insert(socket->peerAddress(), { *socket, typeSocket::CLIENT });
    checkClient();
}

void Connector::slotNewConnectionReceiver()
{
    auto socket = serverReceiver->nextPendingConnection();
    mapSockets.insert(socket->peerAddress(), { *socket, typeSocket::SENDER });
    checkClient();
}

void Connector::slotNewConnectionSender()
{
    auto socket = serverSender->nextPendingConnection();
    mapSockets.insert(socket->peerAddress(), { *socket, typeSocket::RECEIVER });
    checkClient();
}

void Connector::addLogin(QHostAddress ip, QString login)
{
    logins.insert(ip, login);
}

void Connector::checkClient()
{
    if (mapSockets.size() < 3)
        return;
    auto list = mapSockets.uniqueKeys();
    for (auto &elem : list)
    {
        std::vector<std::pair<QTcpSocket &, typeSocket>> vec;
        for (auto it = mapSockets.begin(); it != mapSockets.end(); it++)
        {
            if (it.key() == elem)
            {
                vec.push_back({ it.value().first, it.value().second });
            }
        }
        if (vec.size() == 3)
        {
            QTcpSocket *socClient = nullptr, *socReceiver = nullptr, *socSender = nullptr;
            for (auto &soc : vec)
            {
                if (soc.second == typeSocket::CLIENT)
                {
                    socClient = &soc.first;
                }
                else if (soc.second == typeSocket::RECEIVER)
                {
                    socReceiver = &soc.first;
                }
                else
                {
                    socSender = &soc.first;
                }
            }
            auto log = logins.find(socClient->peerAddress());
            if (log.key() == socClient->peerAddress())
            {
                clientManager->createClient(*socClient, *socSender, *socReceiver,
                                            log.value());
                logins.remove(log.key());
            }
            mapSockets.remove(elem);
        }
    }
}
