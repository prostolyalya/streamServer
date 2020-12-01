#ifndef CLIENT_H
#define CLIENT_H
#pragma once

#include <QtNetwork>
#include <QObject>
class Client : public QObject
{
    Q_OBJECT
public:
    Client(QTcpSocket& _socket, int id, QObject* parent = nullptr);
    ~Client();
    void sendMessage(QString text);

    int getId() const;

private:
    QTcpSocket& socket;
    int id = 0;

public:
public slots:
    void slotRead();
    void slotClientDisconnected();

signals:
    void clientDisconnect(int id);
    void messageReceived(QByteArray msg);
};
#endif // CLIENT_H
