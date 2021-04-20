#ifndef utils_H
#define utils_H
#include <QString>

namespace Utils
{
    enum class LogLevel
    {
        LOW,
        AVERAGE,
        HIGH
    };

    void log(const QString message);
    bool checkConfigFile();
    void readConfigFile();
    void saveConfig();
    void loadConfig();
    static Utils::LogLevel logLevel = LogLevel::AVERAGE;
    static QString filePath = "";
};

#endif // utils_H
