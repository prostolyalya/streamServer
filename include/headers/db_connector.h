#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H
#pragma once

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

class DBConnector
{
public:
    DBConnector(QString dbName);
    bool findUser(QString login);
    bool addUser(QString login, QString password);
    bool loginUser(QString login, QString password);
private:
    QSqlDatabase db;
    QString tableName1 = "users";
    QString tableName2 = "videos";
    QString tableName3 = "audio";
};

#endif // DB_CONNECTOR_H
