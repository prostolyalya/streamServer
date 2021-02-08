#include "server.h"
#include "cryptor.h"
Server::Server(std::shared_ptr<UiController> _uiController,
               QQmlApplicationEngine& _engine)
    : engine(_engine)
    , uiController(_uiController)

{
    connect(uiController.get(), &UiController::init, this, &Server::init);
}

void Server::init()
{
    engine.load(QStringLiteral("qrc:/include/ui/mainServerWindow.qml"));
    threadPool = std::make_unique<ThreadPool>();
    clientManager = std::make_shared<ClientManager>(uiController);
    connector = std::make_unique<Connector>(clientManager);

    connect(clientManager.get()->getAuth().get(), &Authenticator::loginComplete, connector.get(), &Connector::addLogin);
}
