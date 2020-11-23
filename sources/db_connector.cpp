#include "db_connector.h"

DBConnector::DBConnector(QString dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    db.open();
    QSqlQuery query;
    query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName1
                       + " ("
                         "user_id         TEXT , "
                         "user_login      TEXT , "
                         "user_passcode   TEXT ); "));
    query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName2
                       + " ("
                         "user_id   TEXT, "
                         "video_name   TEXT, "
                         "video_path  TEXT ); "));
    query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName2
                       + " ("
                         "user_id   TEXT, "
                         "audio_name   TEXT, "
                         "audio_path  TEXT ); "));
    db.close();
}
