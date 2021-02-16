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

void Sender::setFile_path(const QString &value)
{
    file_path = value;
}

void Sender::sendFile()
{
    QFile file(file_path);
    if (file.open(QFile::ReadOnly))
    {
        int size = 2048;
        for (int pos = 0; pos < file.size(); pos += 2048)
        {
            file.seek(pos);
            QByteArray data = file.read(size);
            while (socket.waitForReadyRead(5)) { }
            socket.write(data);
        }
    }
    QStringList list = file_path.split('/');
    QString name = list.at(list.size() - 1);
    emit fileSent(file.size(), name);
    qDebug() << file.size();
}
