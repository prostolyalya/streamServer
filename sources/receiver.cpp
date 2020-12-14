#include "receiver.h"
#include <QFile>
#include <QHostAddress>

Receiver::Receiver(QTcpSocket&_socket, QString path, QObject *parent)
    : QObject(parent),
      tmp_path(path),
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
        QFile file(tmp_path);
        file.open(QIODevice::Append|QIODevice::WriteOnly);
        file.write(data);
        file.close();
        file_size += data.size();
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

