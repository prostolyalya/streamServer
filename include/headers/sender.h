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

    void setFile_path(const QString &value);
public slots:
    void readSocket();
    void discardSocket();
    void sendFile();
signals:
    void fileSent(qint64, QString);
    void sendFileSignal();
private:
    QTcpSocket& socket;
    QString file_path = "";
};
#endif // SENDER_H
