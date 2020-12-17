#include "sender.h"
Sender::Sender(QTcpSocket &_socket, QObject *parent)
    : QObject(parent)
    , socket(_socket)
{
    connect(&socket, &QTcpSocket::readyRead, this, &Sender::readSocket);
    connect(&socket, &QTcpSocket::disconnected, this, &Sender::discardSocket);
    connect(this, &Sender::sendFileSignal, this, &Sender::sendFile);
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

void Sender::setFile_path(const QString &value)
{
    file_path = value;
}

void Sender::connecting()
{
    socket.connectToHost(QHostAddress::LocalHost, 6002);
}

void Sender::sendFile()
{
    QFile file(file_path);
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
    QStringList list = file_path.split('/');
    QString name = list.at(list.size()-1);
    emit fileSent(file.size(), name);
    qDebug() << file.size();
}


