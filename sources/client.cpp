#include "client.h"

Client::Client(QTcpSocket &_socket, QObject *parent)
    : QObject(parent),
      socket(_socket)
{
    connect(&socket, &QTcpSocket::readyRead, this, &Client::slotRead);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::slotClientDisconnected);
    qDebug() << socket.state();
    if(socket.state() == QAbstractSocket::ConnectedState)
        qDebug() << "Connected to server";
    sendMessage("Hello from server");
}

void Client::sendMessage(QString text)
{
    socket.write(text.toUtf8());
}

void Client::slotRead()
{
    while (socket.bytesAvailable() > 0)
    {
        QByteArray array = socket.readAll();
        qDebug() << array;
    }
}

void Client::slotClientDisconnected()
{
    socket.close();
}
