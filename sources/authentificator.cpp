#include "authentificator.h"
Authenticator::Authenticator(std::shared_ptr<DBConnector> dbase, QObject *parent)
    : db(dbase)
{
    serverAuth = std::make_unique<QTcpServer>(this);
    connect(serverAuth.get(), &QTcpServer::newConnection, this,
            &Authenticator::slotNewConnection);
    if (!serverAuth->listen(QHostAddress::Any, 6003))
    {
        qDebug() << "serverAuth is not started";
    }
    else
    {
        qDebug() << "serverAuth is started";
    }
}

void Authenticator::slotNewConnection()
{
    auto socket = serverAuth->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Authenticator::slotRead,
            Qt::QueuedConnection);
    connect(socket, &QTcpSocket::disconnected, this,
            &Authenticator::slotClientDisconnected, Qt::QueuedConnection);
    qDebug() << "new auth";
    sockets.push_back(socket);
}

void Authenticator::slotRead()
{
    qDebug() << "slotRead";
    QTcpSocket *socket = static_cast<QTcpSocket *>(QObject::sender());
    while (socket->bytesAvailable() > 0)
    {
        QByteArray array = socket->readAll();
        QByteArrayList list = array.split('/');
        QByteArray login = list.at(1);
        QByteArray pass = list.at(2);
        qDebug() << "";
        if (list.at(0) == "login_user")
        {
            qDebug() << "login_user";
            if (db.get()->findUser(login))
            {
                if (db.get()->loginUser(login, pass))
                {
                    emit loginComplete(socket->peerAddress() ,login);
                    socket->write("login_ok");
                    qDebug() << "login_ok";
                    return;
                }
                 qDebug() << "login2_failed";
            }
            qDebug() << "login_failed";
            socket->write("login_failed");
            return;
        }
        else if (list.at(0) == "registration_user")
        {
            qDebug() << "registration_user";
            if (!db.get()->findUser(login))
            {
                if (db.get()->addUser(login, pass))
                {
                    emit loginComplete(socket->peerAddress(), login);
                    socket->write("registration_ok");
                    qDebug() << "registration_ok";
                    return;
                }
            }
            qDebug() << "registration_failed";
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
