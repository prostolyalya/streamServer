#include "stream_client.h"

StreamClient::StreamClient(QObject *parent)
    :QObject(parent)
{
    socket = std::make_unique<QTcpSocket>();
    uiController = std::make_shared<UiController>();
    client = std::make_unique<Client>(*socket.get(), 0);
    connect(uiController.get(), &UiController::sendText, this, &StreamClient::sendText);
    connect(client.get(), &Client::messageReceived, this, &StreamClient::textToUi);
    socket->connectToHost(QHostAddress::LocalHost, 6000);
    if(socket->waitForConnected())
        qDebug() << "Connected to Server";

}

StreamClient::~StreamClient()
{
//    socket->close();
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
