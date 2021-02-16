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
           QString _login, QObject* parent = nullptr);
    ~Client();

    QString getLogin() const;

private:
    QTcpSocket& socket;

    QString login = "";
    qint64 sizeFile = 0;
    std::unique_ptr<Sender> sender;
    std::unique_ptr<Receiver> receiver;

    QString current_path;
    QString fileName = "";
    bool isPrivateFile = true;

    void saveFile();

public:
    void connecting();
public slots:
    void slotRead();
    void slotClientDisconnected();
    void fileSent(qint64 size, QString fileName);
    void sendFile(QString path);
    void sendMessage(QString text);
    void requestFileList(QStringList pubFiles);
signals:
    void clientDisconnect(QString login);
    void messageReceived(QByteArray msg);
    void sendFileSignal();
    void addFileToDB(QString login, QString filename, bool isPrivate);
    void requestPubFiles();
};
#endif // CLIENT_H
