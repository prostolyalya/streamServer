#ifndef SENDER_H
#define SENDER_H
#pragma once
#include <QtNetwork>
#include <QObject>
class Sender : public QObject
{
public:
    Sender(QObject *parent = nullptr);
    ~Sender();
public slots:
    void readSocket();
    void discardSocket();

private:
    std::unique_ptr<QTcpSocket> socket;
};
#endif // SENDER_H
