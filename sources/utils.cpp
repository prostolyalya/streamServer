#include "utils.h"
#include <chrono>
#include <QFile>
#include <iostream>
#include <QDir>
void Utils::log(const QString message)
{
    const auto time =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    QString time_in = std::ctime(&time);
    time_in.chop(6);
    QString message_in = "[" + time_in + "] " + message;
    std::cout << message_in.toStdString() << std::endl;
    QFile file("logs.txt");
    if(file.open(QIODevice::ReadWrite | QFile::Append))
    {
        file.write(message_in.toUtf8() + '\n');
    }
    else
    {
        std::cout << std::string(std::ctime(&time)) + " Can't open log file!";
    }
    file.close();
}

bool Utils::checkConfigFile()
{
    QString file_path = filePath.isEmpty() ? QDir::currentPath() +  "/" + "config" : filePath;
    return QFile::exists(file_path);
}
