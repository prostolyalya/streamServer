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
    struct startParameters
    {
        QString login = "";
        QString password = "";
        QString address_port = "";
        QString folder = "";
        QString log_file = "";
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
    bool checkOptions(const int ac, char *av[], startParameters& param);
    extern QString logFile;
};

#endif // utils_H
