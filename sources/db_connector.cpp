#include "db_connector.h"
#include "utils.h"

DBConnector::DBConnector(QString dbName, QObject *parent)
    : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (db.open())
    {
        QSqlQuery query;
        query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName1
                           + " ("
                             "user_login      TEXT UNIQUE, "
                             "user_password   TEXT ); "));
        query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName2
                           + " ("
                             "user_login   TEXT, "
                             "filename     TEXT ); "));
        query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName3
                           + " ("
                             "user_login   TEXT, "
                             "filename     TEXT ); "));
        db.close();
    }
    else
    {
        Utils::log(db.lastError().text());
    }
}

bool DBConnector::findUser(QString login)
{
    bool find = false;
    if (db.open())
    {
        QSqlQuery query;
        if (query.exec("SELECT user_login FROM " + tableName1 + " WHERE user_login = '"
                       + login + "';"))
        {
            auto res = query.next();
            if (res)
                find = true;
        }
        db.close();
    }
    return find;
}

bool DBConnector::addUser(QString login, QString password)
{
    bool exec = false;
    if (db.open())
    {
        QString insert = "INSERT INTO " + tableName1
            + "(user_login, user_password) "
              "VALUES ('"
            + login + "', '" + password + "');";
        QSqlQuery query;
        exec = query.exec(insert);

        db.close();
    }
    return exec;
}

bool DBConnector::loginUser(QString login, QString password)
{
    bool find = false;
    if (db.open())
    {
        QSqlQuery query;
        if (query.exec("SELECT user_login, user_password FROM " + tableName1
                       + " WHERE user_login = '" + login + "' AND user_password = '"
                       + password + "';"))
        {
            auto res = query.next();
            if (res)
                find = true;
        }
        db.close();
    }
    return find;
}

void DBConnector::addFile(QString login, QString filename, bool isPrivate)
{
    QString tableName = isPrivate ? tableName3 : tableName2;
    if (db.open())
    {
        QString insert = "INSERT INTO " + tableName
            + "(user_login, filename) "
              "VALUES ('"
            + login + "', '" + filename + "');";
        QSqlQuery query;
        query.exec(insert);
        Utils::log(db.lastError().text());
        db.close();
    }
}

void DBConnector::requestPubFiles()
{
    QStringList res;
    if (db.open())
    {
        QSqlQuery query;
        if (query.exec("SELECT * FROM " + tableName2 + " ;"))
        {
            while (query.next())
            {
                QString login = query.value(0).toString();
                QString file = query.value(1).toString();
                res.append(login + "/" + file);
            }
        }
        db.close();
    }
    emit responsePubFiles(res);
}
