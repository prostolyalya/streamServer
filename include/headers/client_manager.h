#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#pragma once

#include <string>
#include <QtNetwork>
#include <vector>
#include <QObject>
#include "client.h"
#include "ui_controller.h"
#include "db_connector.h"

class ClientManager : public QObject
{
    Q_OBJECT
public:
    ClientManager(std::shared_ptr<UiController> ui, QObject *parent = nullptr);
    void createClient(QTcpSocket &socketClient, QTcpSocket &socketSender, QTcpSocket &socketReceiver);

public slots:
    void clientDisconnected(int id);
    void sendMessageToClients(QString text);
    void receiveMessage(QByteArray msg);

private:
    std::shared_ptr<UiController> uiController;
    std::map<int, std::unique_ptr<Client>> clients;
    std::unique_ptr<DBConnector> DB;
    int count_clients = 1;
};
#endif // CLIENTMANAGER_H
