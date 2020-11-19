#ifndef STREAMCLIENT_H
#define STREAMCLIENT_H
#pragma once
#include "client.h"
#include "ui_controller.h"
#include <QTcpSocket>
class StreamClient : public QObject
{
    Q_OBJECT
public:
    StreamClient(QObject *parent = nullptr);
    ~StreamClient();

    std::shared_ptr<UiController> getUiController() const;

public slots:
    void sendText(QString text);
    void textToUi(QString text);
private:

    std::unique_ptr<QTcpSocket> socket;
    std::unique_ptr<Client> client;
    std::shared_ptr<UiController> uiController;
};

#endif // STREAMCLIENT_H
