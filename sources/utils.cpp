#include "utils.h"
#include <chrono>
#include <QFile>
#include <iostream>
#include <QDir>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace Utils {
    QString logFile = "logs.txt";
}

void Utils::log(const QString message)
{
    const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    QString time_in = std::ctime(&time);
    time_in.chop(6);
    QString message_in = "[" + time_in + "] " + message;
    std::cout << message_in.toStdString() << std::endl;
    QFile file(logFile);
    if (file.open(QFile::ReadWrite | QFile::Append))
    {
        file.write(message_in.toUtf8() + '\n');
    }
    else
    {
        std::cout << std::string(std::ctime(&time)) + " Can't open log file!";
    }
    file.close();
}

bool Utils::checkConfigFile(QString filePath)
{
    QString file_path = filePath.isEmpty() ? QDir::currentPath() + "/" + "config" : filePath;
    return QFile::exists(file_path);
}

bool Utils::checkOptions(const int ac, char* av[], startParameters &param)
{
    po::options_description desc("Welcome to streamServer.\nAllowed commands:\nwipe - clear all data;\nexit "
                                 "- shutdown server.\nAllowed options:");
    desc.add_options()("help",
                       "help message")("address_port", po::value<std::string>(),
                                       "server address and port (default ports: 6000, 6001, 6002)")
            ("folder", po::value<std::string>(), "files folder path (default: /data/)")
            ("log_file", po::value<std::string>(), "log file name (default: logs.txt)")
            ("login", po::value<std::string>(), "login")
            ("password", po::value<std::string>(), "password");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return true;
    }
    if (vm.count("address_port"))
    {
        param.address_port = vm["address_port"].as<std::string>().c_str();
    }
    if (vm.count("folder"))
    {
        param.folder = vm["folder"].as<std::string>().c_str();
        if (!param.folder.endsWith("/"))
            param.folder.append("/");
    }
    if (vm.count("log_file"))
    {
        param.log_file = vm["log_file"].as<std::string>().c_str();
    }
    if (vm.count("login"))
    {
        param.login = vm["login"].as<std::string>().c_str();
    }
    if (vm.count("password"))
    {
        param.password = vm["password"].as<std::string>().c_str();
    }

    return false;
}

void Utils::wipe(QString path)
{
    if (path.isEmpty())
    {
        return;
    }
    QDir(path).removeRecursively();
}

void Utils::saveWhiteList(QStringList names, QString path)
{
    QString white("");
    for (const auto& name : names)
    {
        white.append(name + "/");
    }
    white.chop(1);

    QFile file(path + "whitelist");
    if (file.open(QFile::ReadWrite))
    {
        file.resize(0);
        file.write(white.toUtf8());
    }
    file.close();
}

void Utils::loadWhiteList(QStringList& names, QString path)
{
    QString data("");
    QFile file(path + "whitelist");
    if (file.open(QFile::ReadOnly))
    {
        data = file.readAll();
    }
    file.resize(0);
    file.close();
    if (!data.isEmpty())
    {
        names = data.split("/");
    }
}
