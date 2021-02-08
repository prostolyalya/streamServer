#ifndef AUTHENTIFICATOR_H
#define AUTHENTIFICATOR_H

#include <QtNetwork>
#include <QObject>

#include "db_connector.h"

class Authenticator : public QObject
{
    Q_OBJECT
public:
    explicit Authenticator(std::shared_ptr<DBConnector> dbase, QObject *parent = 0);

public slots:
    void slotNewConnection();
    void slotRead();
    void slotClientDisconnected();
signals:
    void loginComplete(QHostAddress ip ,QString login);
private:
    std::unique_ptr<QTcpServer> serverAuth;
    std::shared_ptr<DBConnector> db;
    std::list<QTcpSocket *> sockets;
};

#endif // AUTHENTIFICATOR_H
