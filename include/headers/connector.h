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
    explicit Connector(const QString address ,QObject *parent = 0);
    std::unique_ptr<QTcpServer> serverClients;
    std::unique_ptr<QTcpServer> serverReceiver;
    std::unique_ptr<QTcpServer> serverSender;
public slots:
    void slotNewConnectionClient();
    void slotNewConnectionReceiver();
    void slotNewConnectionSender();
    void addLogin(QHostAddress ip, QString login);
signals:
    void addClient(QTcpSocket *socketClient, QTcpSocket *socketSender,
                   QTcpSocket *socketReceiver, QString login);

private:
    void checkClient();

    enum class typeSocket
    {
        CLIENT,
        SENDER,
        RECEIVER
    };
    QHash<QHostAddress, QTcpSocket *> socketsClient;
    QHash<QHostAddress, QTcpSocket *> socketsSender;
    QHash<QHostAddress, QTcpSocket *> socketsReceiver;

    QHash<QHostAddress, QString> logins;
};
#endif // CONNECTOR_H
