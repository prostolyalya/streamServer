#include "client.h"

Client::Client(QTcpSocket &_socket, QTcpSocket &_socketSender,
               QTcpSocket &_socketReceiver, int id, QObject *parent)
    : QObject(parent)
    , socket(_socket)
    , socketSender(_socketSender)
    , socketReceiver(_socketReceiver)
    , id(id)
{
    connect(&socket, &QTcpSocket::readyRead, this, &Client::slotRead);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::slotClientDisconnected);
    sender = std::make_unique<Sender>(socketSender);
    receiver = std::make_unique<Receiver>(socketReceiver);
    current_path = QDir::currentPath() + "/" + QString::number(id) + "/";
    QDir().mkdir(current_path);
    connect(sender.get(), &Sender::fileSent, this, &Client::fileSent);
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

void Client::saveFile()
{
    if (sizeFile < receiver.get()->cash.size())
        QTimer::singleShot(3000, this, &Client::saveFile);
    while(QFile(current_path + fileName).exists())
        fileName += "1";
    QFile file(current_path + fileName);
    if (file.open(QFile::WriteOnly))
    {
        file.write(receiver->cash);
        file.close();
        receiver->cash.clear();
    }
    emit messageReceived("File received: " + current_path.toUtf8() + fileName.toUtf8());
}

void Client::connecting()
{
    socket.reset();
    socket.connectToHost(QHostAddress::LocalHost, 6000);
    socket.waitForConnected(3000);
    if (socket.state() == QTcpSocket::ConnectedState)
    {
        emit messageReceived("Connected to server");
        sender.get()->connecting();
        receiver.get()->connecting();
    }
    else
    {
        emit messageReceived("Can`t connect to server, reconnecting...");
        QTimer::singleShot(3000, this, &Client::connecting);
    }
}

void Client::slotRead()
{
    while (socket.bytesAvailable() > 0)
    {
        QByteArray array = socket.readAll();
        if (array.startsWith("end_of_file"))
        {
            QByteArrayList list = array.split('/');
            QByteArray data = list.at(1);
            fileName = list.at(2);
            sizeFile = data.toInt();
            QTimer::singleShot(1000, this, &Client::saveFile);
        }
        else
            emit messageReceived("From " + (id == 0 ? "server" : QByteArray::number(id))
                                 + ": " + array);
    }
}

void Client::slotClientDisconnected()
{
    socket.close();
    emit clientDisconnect(id);
}

void Client::fileSent(qint64 size, QString fileName)
{
    socket.write("end_of_file/" + QByteArray::number(size) + "/" + fileName.toUtf8());
}

void Client::sendFile(QString path)
{
    emit messageReceived("Send file: " + path.mid(7).toUtf8());
    sender.get()->sendFile(path);
}
