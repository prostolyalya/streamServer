#ifndef STARTER_H
#define STARTER_H
#pragma once

#include <qqml.h>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "server.h"
#include "stream_client.h"

class Starter : public QObject
{
    Q_OBJECT
public:
    Starter(QQmlApplicationEngine &engine);

public slots:
    void startServer(QString username, QString password);
    void startClient(QString username, QString password);
private:
    void serverStart(QString username, QString password);
    void clientStart(QString username, QString password);

    std::unique_ptr<Server> server;
    std::unique_ptr<StreamClient> client;
    QQmlApplicationEngine &engine;
};

#endif // STARTER_H
