#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H
#pragma once

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

class DBConnector : public QObject
{
    Q_OBJECT
public:
    DBConnector(QString dbName, QObject* parent = nullptr);
    bool findUser(QString login);
    bool addUser(QString login, QString password);
    bool loginUser(QString login, QString password);

public slots:
    void addFile(QString login, QString filename, bool isPrivate);
    void requestPubFiles();
signals:
    void responsePubFiles(QStringList);

private:
    QSqlDatabase db;
    QString tableName1 = "users";
    QString tableName2 = "publicFiles";
    QString tableName3 = "privateFiles";
};

#endif // DB_CONNECTOR_H
