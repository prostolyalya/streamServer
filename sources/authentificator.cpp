#include "authentificator.h"
#include "utils.h"
Authenticator::Authenticator(std::shared_ptr<DBConnector> dbase, QString address, QObject *parent)
    : QObject(parent)
    , db(dbase)
{
    serverAuth = std::make_unique<QTcpServer>(this);
    connect(serverAuth.get(), &QTcpServer::newConnection, this,
            &Authenticator::slotNewConnection);
    int port = 6003;
    QHostAddress _address = QHostAddress::Any;
    if (!address.isEmpty())
    {
        QStringList list = address.split(":");
        _address = QHostAddress(list.at(0));
        port = list.at(1).toInt();
    }
    Utils::log("server address is " + _address.toString());
    if (!serverAuth->listen(_address, port))
    {
        Utils::log("serverAuth is not started");
    }
    else
    {
        Utils::log("serverAuth is started: " + QString::number(port));
    }
}

void Authenticator::slotNewConnection()
{
    auto socket = serverAuth->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Authenticator::slotRead,
            Qt::QueuedConnection);
    connect(socket, &QTcpSocket::disconnected, this,
            &Authenticator::slotClientDisconnected, Qt::QueuedConnection);
    sockets.push_back(socket);
}

void Authenticator::slotRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(QObject::sender());
    while (socket->bytesAvailable() > 0)
    {
        QByteArray array = socket->readAll();
        QByteArrayList list = array.split('/');
        QByteArray login = list.at(1);
        QByteArray pass = list.at(2);
        QString log_string = " " + login + " "
            + socket->peerAddress().toString().right(3);
        if (list.at(0) == "login_user")
        {
            Utils::log("login_user" + log_string);
            if (db.get()->findUser(login))
            {
                if (db.get()->loginUser(login, pass))
                {
                    emit loginComplete(socket->peerAddress(), login);
                    socket->write("login_ok");
                    Utils::log("login_ok" + log_string);
                    return;
                }
            }
            Utils::log("login_failed" + log_string);
            socket->write("login_failed");
            return;
        }
        else if (list.at(0) == "registration_user")
        {
            Utils::log("registration_user " + log_string);
            if (!db.get()->findUser(login))
            {
                if (db.get()->addUser(login, pass))
                {
                    emit loginComplete(socket->peerAddress(), login);
                    socket->write("registration_ok");
                    Utils::log("registration_ok " + log_string);
                    return;
                }
            }
            Utils::log("registration_failed " + log_string);
            socket->write("registration_failed");
            return;
        }
    }
}

void Authenticator::slotClientDisconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket *>(QObject::sender());
    sockets.remove(socket);
}
