#include "stream_client.h"

StreamClient::StreamClient(QObject *parent)
    :QObject(parent)
{
    thread_pool = std::make_unique<ThreadPool>();
    socket = std::make_unique<QTcpSocket>();
    socketSender = std::make_unique<QTcpSocket>();
    socketReceiver = std::make_unique<QTcpSocket>();
    uiController = std::make_shared<UiController>();
    client = std::make_unique<Client>(*socket.get(), *socketSender.get(), *socketReceiver.get(), 0);
    connect(uiController.get(), &UiController::sendText, this, &StreamClient::sendText);
    connect(client.get(), &Client::messageReceived, this, &StreamClient::textToUi);
    connect(uiController.get(), &UiController::sendFile, client.get(), &Client::sendFile);
    ThreadPool::getInstance()->addToThread(uiController.get());
    client.get()->connecting();

}

StreamClient::~StreamClient()
{

}

void StreamClient::textToUi(QString text)
{
    uiController.get()->addText(text);
}

std::shared_ptr<UiController> StreamClient::getUiController() const
{
    return uiController;
}

bool StreamClient::checkClient(QString username, QString password)
{
    return true;
}

void StreamClient::sendText(QString text)
{
    client.get()->sendMessage(text);
}
