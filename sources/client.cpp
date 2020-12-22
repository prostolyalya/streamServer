#include "client.h"
#include "thread_pool.h"
Client::Client(QTcpSocket& _socket, QTcpSocket& _socketSender,
               QTcpSocket& _socketReceiver, int id, QObject* parent)
    : QObject(parent)
    , socket(_socket)
    , id(id)
{
    current_path = QDir::currentPath() + "/" + QString::number(id) + "/";
    QDir().mkdir(current_path);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::slotRead);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::slotClientDisconnected);
    sender = std::make_unique<Sender>(_socketSender);
    receiver = std::make_unique<Receiver>(_socketReceiver, current_path + "tmp");
    connect(sender.get(), &Sender::fileSent, this, &Client::fileSent);
    connect(this, &Client::sendFileSignal, sender.get(), &Sender::sendFile);
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
            emit messageReceived("File received: " + current_path.toUtf8()
                                 + fileName.toUtf8());
        }
        else
        {
            emit messageReceived("Error with receive file!");
        }
        receiver->file_size = 0;
        receiver.get()->clearTmpFile();
        sizeFile = 0;
    }
}

void Client::requestFileList()
{
    QDir dir(current_path);
    QStringList list = dir.entryList();
    QByteArray data = "response_list_file&";
    for (auto & name : list)
    {
        if(name == "." || name == "..")
            continue;
        data += "/" + name.toUtf8();
    }
    socket.write(data);
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
        else if (array.startsWith("request_file"))
        {
            QByteArrayList list = array.split('/');
            QByteArray data = list.at(1);
            if (QFile::exists(current_path + data))
            {
                sendFile(current_path + data);
            }
        }
        else if (array == "request_list_file")
        {
            requestFileList();
        }
        else
            emit messageReceived("From " + QByteArray::number(id) + ": " + array);
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
    emit messageReceived("Request file: " + path.toUtf8());
    sender.get()->setFile_path(path);
    emit sendFileSignal();
    //    auto f = std::bind(&Sender::sendFileSignal, sender.get());
    //    ThreadPool::getInstance()->addToThread(f);
}
