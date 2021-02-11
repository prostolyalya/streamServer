#include "ui_controller.h"

UiController::UiController(QObject *parent)
    : QObject(parent)
{
}

UiController::~UiController()
{
}

void UiController::addText(QString text)
{
    textServer += text + '\n';
    emit textServerChanged();
}

void UiController::loginComplete(bool complete)
{
    if (complete)
    {
        setErrorText("y");
        emit errorTextChanged();
    }
    else
    {
        setErrorText("X");
        emit errorTextChanged();
    }
}

QString UiController::getErrorText() const
{
    return errorText;
}

void UiController::setErrorText(const QString &value)
{
    errorText = value;
}

QString UiController::getText() const
{
    return textServer;
}

void UiController::setText(const QString &value)
{
    textServer = value;
}
