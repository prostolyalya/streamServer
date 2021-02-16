#include "client.h"
#include "thread_pool.h"
Client::Client(QTcpSocket& _socket, QTcpSocket& _socketSender,
               QTcpSocket& _socketReceiver, QString _login, QObject* parent)
    : QObject(parent)
    , socket(_socket)
    , login(_login)
{
    current_path = QDir::currentPath() + "/" + login + "/";
    QDir().mkdir(current_path);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::slotRead,
            Qt::QueuedConnection);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::slotClientDisconnected,
            Qt::QueuedConnection);
    sender = std::make_unique<Sender>(_socketSender);
    receiver = std::make_unique<Receiver>(_socketReceiver, current_path + "tmp");
    connect(sender.get(), &Sender::fileSent, this, &Client::fileSent);
    connect(this, &Client::sendFileSignal, sender.get(), &Sender::sendFile,
            Qt::QueuedConnection);
}

Client::~Client()
{
    qDebug() << login << " deleted";
}

void Client::sendMessage(QString text)
{
    socket.write(text.toUtf8());
}

QString Client::getLogin() const
{
    return login;
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
            emit addFileToDB(login, fileName, isPrivateFile);
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

void Client::requestFileList(QStringList pubFiles)
{
    qDebug() << "request file list";
    QDir dir(current_path);
    QStringList list = dir.entryList();
    QByteArray data = "response_list_file&";
    for (auto& name : list)
    {
        if (name == "." || name == "..")
            continue;
        data += "/" + name.toUtf8();
    }
    if (!pubFiles.isEmpty())
    {
        data.append("&");
        for (auto& name : pubFiles)
        {
            if (name == "." || name == "..")
                continue;
            data += "//" + name.toUtf8();
        }
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
            isPrivateFile = list.at(3).toInt();
            QTimer::singleShot(1000, this, &Client::saveFile);
        }
        else if (array.startsWith("request_file"))
        {
            QByteArrayList list = array.split('/');
            if (list.size() > 2)
            {
                QByteArray data = list.at(2);
                QString path = QDir::currentPath() + "/" + list.at(1) + "/" + data;
                if (QFile::exists(path))
                {
                    sendFile(path);
                }
            }
            else
            {
                QByteArray data = list.at(1);
                if (QFile::exists(current_path + data))
                {
                    sendFile(current_path + data);
                }
            }
        }
        else if (array.startsWith("request_list_file"))
        {
            emit requestPubFiles();
        }
        else
            emit messageReceived("From " + login.toLatin1() + ": " + array);
    }
}

void Client::slotClientDisconnected()
{
    socket.close();
    emit clientDisconnect(login);
}

void Client::fileSent(qint64 size, QString fileName)
{
    socket.write("end_of_file/" + QByteArray::number(size) + "/" + fileName.toUtf8());
    emit messageReceived("File sent: " + fileName.toUtf8());
}

void Client::sendFile(QString path)
{
    qDebug() << "request file";
    emit messageReceived("Request file: " + path.toUtf8());
    sender.get()->setFile_path(path);
    emit sendFileSignal();
    //    auto f = std::bind(&Sender::sendFileSignal, sender.get());
    //    ThreadPool::getInstance()->addToThread(f);
}
