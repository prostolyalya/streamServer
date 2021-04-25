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
#include "authentificator.h"

class ClientManager : public QObject
{
    Q_OBJECT
public:
    ClientManager(std::shared_ptr<UiController> ui, QString _path, QObject *parent = nullptr);
    std::shared_ptr<Authenticator> getAuth();

    QStringList getClients();

public slots:
    void clientDisconnected(QString login);
    void createClient(QTcpSocket *socketClient, QTcpSocket *socketSender,
                      QTcpSocket *socketReceiver, QString login);

private:
    std::shared_ptr<UiController> uiController;
    std::shared_ptr<Authenticator> auth;
    std::map<QString, std::unique_ptr<Client>> clients;
    std::shared_ptr<DBConnector> DB;
    const QString path;
signals:
    void sendMessageToAll(QString text);
};
#endif // CLIENTMANAGER_H
