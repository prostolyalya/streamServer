#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H
#pragma once

#include <QObject>
#include <qqml.h>

class UiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uiText READ getText WRITE setText NOTIFY textServerChanged)
public:
    UiController(QObject* parent = nullptr);
    ~UiController();

    QString getText() const;

    void setText(const QString& value);
public slots:
    void addText(QString text);
signals:
    void textServerChanged();
    void sendTextAllUsers(QString text);
    void sendText(QString text);
    void sendFile(QString path);
    void init(QString login, QString pass);
private:
    QString textServer;
};

#endif // UI_CONTROLLER_H
