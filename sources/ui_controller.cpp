#include "ui_controller.h"

UiController::UiController(QObject *parent)
    : QObject(parent)
{
}

UiController::~UiController()
{
}

void UiController::addTextServer(QString text)
{
    textServer += text + '\n';
    emit textServerChanged();
}

QString UiController::getTextServer() const
{
    return textServer;
}

void UiController::setTextServer(const QString &value)
{
    textServer = value;
}

