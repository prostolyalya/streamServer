#include "sender.h"
Sender::Sender(QTcpSocket &_socket, QObject *parent)
    : QObject(parent)
    , socket(_socket)
{
    connect(&socket, &QTcpSocket::readyRead, this, &Sender::readSocket);
    connect(&socket, &QTcpSocket::disconnected, this, &Sender::discardSocket);
}

void Sender::readSocket()
{
    if (socket.bytesAvailable() > 0)
        qDebug() << socket.readAll();
}

void Sender::discardSocket()
{
    socket.deleteLater();
}

void Sender::connecting()
{
    socket.connectToHost(QHostAddress::LocalHost, 6002);
}

void Sender::sendFile(QString path)
{
    path = path.mid(7);
    QFile file(path);
    if (file.open(QFile::ReadOnly))
    {
        int size = 64;
        for (int pos = 0; pos < file.size(); pos += 64)
        {
            file.seek(pos);
            QByteArray data = file.read(size);
            socket.write(data);
        }
    }
    QStringList list = path.split('/');
    QString name = list.at(list.size()-1);
    emit fileSent(file.size(), name);
}
