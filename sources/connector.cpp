#include "headers/connector.h"
#include <QCoreApplication>

Connector::Connector(std::shared_ptr<ClientManager> _clientManager, QObject *parent)
    : QObject(parent)
    , clientManager(_clientManager)
{
    server = std::make_unique<QTcpServer>(this);

    connect(server.get(), &QTcpServer::newConnection, this,
            &Connector::slotNewConnection);

    if (!server->listen(QHostAddress::Any, 6000))
    {
        qDebug() << "server is not started";
    }
    else
    {
        qDebug() << "server is started";
    }
}

void Connector::slotNewConnection()
{
    auto socket = server->nextPendingConnection();
    clientManager->createClient(*socket);
}
