#include "ui_controller.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <QFile>
#include "utils.h"

UiController::UiController(QObject *parent)
    : QObject(parent)
{
}

UiController::~UiController()
{
}

void UiController::addText(QString text)
{
    Utils::log(text);
}

void UiController::loginComplete(bool complete, QString path)
{
    if (complete)
    {
        Utils::log("Login complete");
    }
    else
    {
        Utils::log("Login incorrect");
        startLogin(path);
    }
}

void UiController::startLogin(QString path)
{
    bool reg = !QFile::exists(path + "profile");
    if(reg)
    {
        Utils::log("Welcome to Stream Server, please input your login and password");
    }
    else
    {
        Utils::log("Glad to see you again");
    }

    std::string log, pass;

    Utils::log("Login:");
    std::cin >> log;
    Utils::log(log.c_str());
    Utils::log("Password:");
    std::cin >> pass;
    Utils::log(pass.c_str());
    emit login(log.c_str(), pass.c_str(), reg);
}
