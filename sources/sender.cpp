#include "sender.h"
Sender::Sender(QObject *parent)
    : QObject(parent)
{
    socket = std::make_unique<QTcpSocket>();
    connect(socket.get(), &QTcpSocket::readyRead, this, &Sender::readSocket);
    connect(socket.get(),&QTcpSocket::disconnected, this, &Sender::discardSocket);
    socket->connectToHost(QHostAddress::LocalHost, 6000);
    if(socket->waitForConnected())
        qDebug() << "Connected to Server";
    socket->write("Hello from client");
}

void Sender::readSocket()
{
    if(socket->bytesAvailable() > 0)
        qDebug() << socket->readAll();
}

void Sender::discardSocket()
{
    socket->deleteLater();

    qDebug() << "Disconnected!";
}
