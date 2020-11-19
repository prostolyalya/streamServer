#include "client.h"

Client::Client(QTcpSocket &_socket, int id, QObject *parent)
    : QObject(parent)
    , socket(_socket)
    , id(id)
{
    connect(&socket, &QTcpSocket::readyRead, this, &Client::slotRead);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::slotClientDisconnected);
    qDebug() << socket.state();
    if (socket.state() == QAbstractSocket::ConnectedState)
        qDebug() << "Connected to server";
    else
        qDebug() << "Can`t connect to server";

    sendMessage("Hello from server");
}

Client::~Client()
{
    qDebug() << "Client" << id << "deleted";
}

void Client::sendMessage(QString text)
{
    socket.write(text.toUtf8());
}

int Client::getId() const
{
    return id;
}

void Client::slotRead()
{
    while (socket.bytesAvailable() > 0)
    {
        QByteArray array = socket.readAll();
        qDebug() << array;
        emit messageReceived("From " + QByteArray::number(id) + ": " + array);
    }

}

void Client::slotClientDisconnected()
{
    qDebug() << "client disconnect";
    socket.close();
    emit clientDisconnect(id);
}
