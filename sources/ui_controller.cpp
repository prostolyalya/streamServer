#include "ui_controller.h"
#include <iostream>
#include <string>
#include <stdio.h>
UiController::UiController(QObject *parent)
    : QObject(parent)
{
}

UiController::~UiController()
{
}

void UiController::addText(QString text)
{
    std::cout << text.toStdString() << std::endl;
}

void UiController::loginComplete(bool complete)
{
    system("clear");
    if (complete)
    {
        addText("Login complete");
    }
    else
    {
        addText("Login incorrect");
        startLogin();
    }
}

void UiController::startLogin()
{
    std::cout << "login (l) / registration (r) ? -> ";
    char val;
    std::cin >> val;
    bool ex = true;
    while (ex)
    {
        bool reg = false;
        switch (val)
        {
        case 'r':
        case 'R':
            reg = true;
        case 'l':
        case 'L': {
            std::string log, pass;

            std::cout << "Login name:";
            std::cin >> log;
            std::cout << "Password:";
            std::cin >> pass;
            emit login(log.c_str(), pass.c_str(), reg);
            ex = false;
            break;
        }
        default:
            std::cout << "Incorrect input, try again";
            break;
        }
    }
}
