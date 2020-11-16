#include "server.h"

Server::Server()
{
//    threadPool = std::make_shared<ThreadPool>();
    clientManager = std::make_shared<ClientManager>();
    connector  = std::make_unique<Connector>(clientManager);
}
