#include <QCoreApplication>
#include "server.h"
#include "sender.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    auto sender = std::make_unique<Server>();
    auto sender = std::make_unique<Sender>();
    return a.exec();
}
