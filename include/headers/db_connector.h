#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H
#pragma once
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
class DBConnector
{
public:
    DBConnector(QString dbName);
private:
    QSqlDatabase db;
    QString tableName1 = "users";
    QString tableName2 = "videos";
    QString tableName3 = "audio";
};

#endif // DB_CONNECTOR_H
