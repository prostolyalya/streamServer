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
    std::unique_ptr<QTcpServer> server;

public slots:
    void slotNewConnection();

private:
    std::shared_ptr<ClientManager> clientManager;
};
#endif // CONNECTOR_H
