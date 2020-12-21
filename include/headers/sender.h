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

    void connecting(QHostAddress host = QHostAddress::Any);

    void setFile_path(const QString &value);
    void setSender_socket(QTcpSocket *value);

public slots:
    void readSocket();
    void discardSocket();
    void sendFile();
signals:
    void fileSent(qint64, QString);
    void sendFileSignal();
private:
    QTcpSocket& socket;
    std::unique_ptr<QTcpSocket> sender_socket;
    QString file_path = "";
};
#endif // SENDER_H
