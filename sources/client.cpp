#include "client.h"

Client::Client(QTcpSocket &_socket, QObject *parent): socket(_socket), QObject(parent)
{
    connect(&socket, &QTcpSocket::readyRead, this, &Client::slotRead);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::slotClientDisconnected);
    qDebug() << socket.state();
    socket.write("Connected\n");
}

void Client::slotRead()
{
    while(socket.bytesAvailable() > 0)
    {
        QByteArray array = socket.readAll();

        socket.write("server: " + array);
    }
}

void Client::slotClientDisconnected()
{
    qDebug() << "socket closed";
    socket.close();
}
