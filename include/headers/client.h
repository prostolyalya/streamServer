#ifndef CLIENT_H
#define CLIENT_H
#pragma once

#include <QtNetwork>
#include <QObject>

#include "sender.h"
#include "receiver.h"

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QTcpSocket& _socket, QTcpSocket& _socketSender, QTcpSocket& _socketReceiver,
           int id, QObject* parent = nullptr);
    ~Client();
    void sendMessage(QString text);

    int getId() const;

private:
    std::unique_ptr<QTcpSocket> sock;
    QTcpSocket& socket;
    QTcpSocket& socketSender;
    QTcpSocket& socketReceiver;
    int id = 0;
    qint64 sizeFile = 0;
    std::unique_ptr<Sender> sender;
    std::unique_ptr<Receiver> receiver;

    QString current_path;
    QString fileName = "";

    void saveFile();

public:
    void connecting();
    void set_sockets(QTcpSocket* socket, QTcpSocket* socket_sender,
                           QTcpSocket* socket_receiver);
    void moveSenderToThread();
public slots:
    void slotRead();
    void slotClientDisconnected();
    void fileSent(qint64 size, QString fileName);
    void sendFile(QString path);
signals:
    void clientDisconnect(int id);
    void messageReceived(QByteArray msg);
};
#endif // CLIENT_H
