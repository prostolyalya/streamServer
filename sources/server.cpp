#include "server.h"

Server::Server()
{
    //    threadPool = std::make_shared<ThreadPool>();
    uiController = std::make_shared<UiController>();
    clientManager = std::make_shared<ClientManager>(uiController);
    connector = std::make_unique<Connector>(clientManager);
}

std::shared_ptr<UiController> Server::getUiController() const
{
    return uiController;
}
