#include "connector.h"
#include "utils.h"
#include <QCoreApplication>
#include <set>
Connector::Connector(QObject* parent)
    : QObject(parent)
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
        Utils::log("serverClients is not started");
    }
    else
    {
        Utils::log("serverClients is started");
    }
    if (!serverReceiver->listen(QHostAddress::Any, 6001))
    {
        Utils::log("serverReceiver is not started");
    }
    else
    {
        Utils::log("serverReceiver is started");
    }
    if (!serverSender->listen(QHostAddress::Any, 6002))
    {
        Utils::log("serverSender is not started");
    }
    else
    {
        Utils::log("serverSender is started");
    }
    const QHostAddress& localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress& address : QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {
            const auto addr = address.toString();
            if (addr.startsWith("192.168"))
                Utils::log(addr + " - Local address");
            else
                Utils::log(addr + " - Global address");
        }
    }
}

void Connector::slotNewConnectionClient()
{
    auto socket = serverClients->nextPendingConnection();
    socketsClient.insert(socket->peerAddress(), socket);
    checkClient();
}

void Connector::slotNewConnectionReceiver()
{
    auto socket = serverReceiver->nextPendingConnection();
    socketsSender.insert(socket->peerAddress(), socket);
    checkClient();
}

void Connector::slotNewConnectionSender()
{
    auto socket = serverSender->nextPendingConnection();
    socketsReceiver.insert(socket->peerAddress(), socket);
    checkClient();
}

void Connector::addLogin(QHostAddress ip, QString login)
{
    logins.insert(ip, login);
}

void Connector::checkClient()
{
    if (socketsClient.empty())
        return;
    for (auto it = socketsClient.begin(); it != socketsClient.end(); it++)
    {
        const auto receiverIt = socketsReceiver.find(it.key());
        const auto senderIt = socketsSender.find(it.key());
        const auto log = logins.find(it.key());
        if (receiverIt == socketsReceiver.end() || senderIt == socketsSender.end()
            || log == logins.end())
        {
            return;
        }
        else
        {
            emit addClient(it.value(), senderIt.value(), receiverIt.value(), log.value());
            logins.remove(log.key());
            socketsReceiver.remove(receiverIt.key());
            socketsSender.remove(senderIt.key());
            socketsClient.remove(it.key());
        }
    }
}
