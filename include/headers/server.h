#ifndef SERVER_H
#define SERVER_H
#pragma once

#include "thread_pool.h"
#include "connector.h"
#include "ui_controller.h"

class Server
{
public:
    Server();

    std::shared_ptr<UiController> getUiController() const;

    static bool checkLogin(QString username, QString password);
private:
    //    std::shared_ptr<ThreadPool> threadPool;
    std::shared_ptr<ClientManager> clientManager;
    std::unique_ptr<Connector> connector;
    std::shared_ptr<UiController> uiController;
    std::unique_ptr<ThreadPool> threadPool;
};

#endif // SERVER_H
