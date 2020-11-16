#ifndef SERVER_H
#define SERVER_H
#pragma once

#include "thread_pool.h"
#include "client_manager.h"
#include "connector.h"

class Server
{
public:
    Server();
private:
//    std::shared_ptr<ThreadPool> threadPool;
    std::shared_ptr<ClientManager> clientManager;
    std::unique_ptr<Connector> connector;
};

#endif // SERVER_H
