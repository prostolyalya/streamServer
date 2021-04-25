#ifndef SERVER_H
#define SERVER_H
#pragma once

#include "thread_pool.h"
#include "connector.h"
#include "ui_controller.h"
#include "authentificator.h"
#include "utils.h"
class Server : public QObject
{
    Q_OBJECT
public:
    Server(std::shared_ptr<UiController> _uiController);
    void init();
public slots:
    void login(QString login, QString password, bool reg);
    void checkInput();
signals:
    void loginComplete(bool complete, QString path = "");
private:
    const QString filePath;
    std::unique_ptr<ClientManager> clientManager;
    std::shared_ptr<UiController> uiController;
    std::unique_ptr<Connector> connector;
    std::unique_ptr<ThreadPool> threadPool;
};

#endif // SERVER_H
