#include "client.h"
#include "thread_pool.h"
Client::Client(QTcpSocket &_socket, QTcpSocket &_socketSender,
               QTcpSocket &_socketReceiver, int id, QObject *parent)
    : QObject(parent)
    , socket(_socket)
    , socketSender(_socketSender)
    , socketReceiver(_socketReceiver)
    , id(id)
{
    current_path = QDir::currentPath() + "/" + QString::number(id) + "/";
    QDir().mkdir(current_path);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::slotRead);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::slotClientDisconnected);
    sender = std::make_unique<Sender>(socketSender);
    receiver = std::make_unique<Receiver>(socketReceiver, current_path + "tmp");
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
    if (sizeFile < receiver.get()->file_size)
        QTimer::singleShot(3000, this, &Client::saveFile);
    else
    {
        while (QFile(current_path + fileName).exists())
            fileName.push_front("1");
        QFile file(current_path + "tmp");
        if (file.size() < sizeFile)
        {
            QTimer::singleShot(3000, this, &Client::saveFile);
            return;
        }
        if (file.open(QFile::ReadOnly))
        {

            file.rename(current_path + fileName);
            receiver->file_size = 0;
            emit messageReceived("File received: " + current_path.toUtf8()
                                 + fileName.toUtf8());
        }
        receiver.get()->clearTmpFile();
    }
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
    emit messageReceived("File sent: " + fileName.toUtf8());
}

void Client::sendFile(QString path)
{
    path = path.mid(7);
    emit messageReceived("Send file: " + path.toUtf8());
    sender.get()->setFile_path(path);
    auto f = std::bind(&Sender::sendFileSignal, sender.get());
    ThreadPool::getInstance()->addToThread(f);
}
