#ifndef SENDER_H
#define SENDER_H
#pragma once

#include <QtNetwork>
#include <QObject>

class Sender : public QObject
{
    Q_OBJECT
public:
    Sender(QTcpSocket& _socket, QObject *parent = nullptr);

    void connecting();
    void sendFile(QString path);
public slots:
    void readSocket();
    void discardSocket();
signals:
    void fileSent(qint64, QString);
private:
    QTcpSocket& socket;
};
#endif // SENDER_H
