#ifndef CLIENT_H
#define CLIENT_H
#pragma once
#include <QtNetwork>
#include <QObject>
class Client : public QObject
{
public:
    Client(QTcpSocket &_socket, QObject * parent = nullptr);
public:
    QTcpSocket& socket;
public slots:
    void slotRead();
    void slotClientDisconnected();
};
#endif // CLIENT_H
