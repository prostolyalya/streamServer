#ifndef SERVER_H
#define SERVER_H
#pragma once

#include "thread_pool.h"
#include "client_manager.h"
class Server
{
    Server();
private:
    ThreadPool* threadPool = nullptr;
    ClientManager* clientManager = nullptr;

};

#endif // SERVER_H
