#ifndef RECEIVER_H
#define RECEIVER_H
#pragma once
#include <QTcpSocket>
#include <QObject>

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver(QTcpSocket &_socket, QString path, QObject* parent = nullptr);

    void connecting();
    void clearTmpFile();
    QString tmp_path = "";
    qint64 file_size = 0;

public slots:
    void slotRead();
    void slotDisconnected();

private:
    QTcpSocket& socket;
};
#endif // RECEIVER_H
