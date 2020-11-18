#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QObject>
class Client : public QObject
{
public:
    Client(QTcpSocket& _socket, QObject* parent = nullptr);
    void sendMessage(QString text);

private:
    QTcpSocket& socket;
public slots:
    void slotRead();
    void slotClientDisconnected();
};
#endif // CLIENT_H
