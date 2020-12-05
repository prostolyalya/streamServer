#ifndef RECEIVER_H
#define RECEIVER_H
#pragma once
#include <QTcpSocket>
#include <QObject>

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver(QTcpSocket &_socket, QObject* parent = nullptr);

    void connecting();

    QByteArray cash = "";
public slots:
    void slotRead();
    void slotDisconnected();

private:
    QTcpSocket& socket;
};
#endif // RECEIVER_H
