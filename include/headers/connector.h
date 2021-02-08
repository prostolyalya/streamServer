#ifndef CONNECTOR_H
#define CONNECTOR_H
#pragma once

#include <QtNetwork>
#include <QObject>
#include "client_manager.h"

class Connector : public QObject
{
    Q_OBJECT
public:
    explicit Connector(std::shared_ptr<ClientManager> _clientManager,
                       QObject *parent = 0);
    std::unique_ptr<QTcpServer> serverClients;
    std::unique_ptr<QTcpServer> serverReceiver;
    std::unique_ptr<QTcpServer> serverSender;
public slots:
    void slotNewConnectionClient();
    void slotNewConnectionReceiver();
    void slotNewConnectionSender();
    void addLogin(QHostAddress ip, QString login);
private:
    void checkClient();

    enum class typeSocket
    {
        CLIENT,
        SENDER,
        RECEIVER
    };
    QMultiHash<QHostAddress, std::pair<QTcpSocket&, typeSocket>> mapSockets;
    std::shared_ptr<ClientManager> clientManager;
    QHash<QHostAddress, QString> logins;
};
#endif // CONNECTOR_H
