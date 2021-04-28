#include "ui_controller.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <QFile>
#include <curses.h>
#include <unistd.h>
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

void UiController::startLogin(QString path, QString _login, QString _password)
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
    if (!_login.isEmpty())
    {
        Utils::log("Login: " + _login);
        log = _login.toStdString();
    }
    else
    {
        Utils::log("Login:");
        std::cin >> log;
    }
    if (!_password.isEmpty())
    {
        pass = _password.toStdString();
    }
    else
    {
        pass = getpass("Password:");
    }

    Utils::log("Password: " + QString (10, '*'));
    emit login(log.c_str(), pass.c_str(), reg);
}
