#ifndef SERVER_H
#define SERVER_H
#pragma once

#include "thread_pool.h"
#include "connector.h"
#include "ui_controller.h"
#include <QQmlApplicationEngine>
class Server : public QObject
{
    Q_OBJECT
public:
    Server(std::shared_ptr<UiController> _uiController,QQmlApplicationEngine & _engine);

    static bool checkLogin(QString username, QString password);

public slots:
    void init(QString login, QString pass);
private:
    QQmlApplicationEngine & engine;
    std::shared_ptr<ClientManager> clientManager;
    std::shared_ptr<UiController> uiController;
    std::unique_ptr<Connector> connector;
    std::unique_ptr<ThreadPool> threadPool;
};

#endif // SERVER_H
