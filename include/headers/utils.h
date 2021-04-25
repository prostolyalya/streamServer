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
    bool checkConfigFile(QString filePath);
    void readConfigFile();
    void saveConfig();
    void loadConfig();
    void wipe(QString path);
    void setFilePath(QString path);
    void saveWhiteList(QStringList names, QString path);
    void loadWhiteList(QStringList& names, QString path);
    bool checkOptions(const int ac, char *av[]);
};

#endif // utils_H
