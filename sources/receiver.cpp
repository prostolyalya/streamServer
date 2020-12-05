#include "receiver.h"

#include <QHostAddress>

Receiver::Receiver(QTcpSocket&_socket, QObject *parent)
    : QObject(parent),
      socket(_socket)
{
    connect(&socket, &QTcpSocket::readyRead, this, &Receiver::slotRead);
    connect(&socket, &QTcpSocket::disconnected, this, &Receiver::slotDisconnected);
}

void Receiver::slotRead()
{
    while (socket.bytesAvailable() > 0)
    {
        QByteArray data = socket.readAll();
        cash += data;
    }
}

void Receiver::slotDisconnected()
{
    socket.deleteLater();
}

void Receiver::connecting()
{
     socket.connectToHost(QHostAddress::LocalHost, 6001);
}

