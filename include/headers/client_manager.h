#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#pragma once
#include <map>
#include <string>
#include "client.h"
class ClientManager
{
private:
    std::map<std::string, Client> clients;
};
#endif // CLIENTMANAGER_H
