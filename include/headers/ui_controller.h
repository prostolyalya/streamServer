#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H
#pragma once

#include <QObject>
#include <qqml.h>

class UiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uiText READ getText WRITE setText NOTIFY textServerChanged)
    Q_PROPERTY(QString uiError READ getErrorText WRITE setErrorText NOTIFY errorTextChanged)
public:
    UiController(QObject* parent = nullptr);
    ~UiController();

    QString getText() const;

    void setText(const QString& value);
    QString getErrorText() const;
    void setErrorText(const QString &value);

public slots:
    void addText(QString text);
    void loginComplete(bool complete);
signals:

    void errorTextChanged();
    void textServerChanged();
    void sendTextAllUsers(QString text);
    void sendText(QString text);
    void sendFile(QString path);
    void login(QString login, QString pass, bool reg);
private:
    QString textServer;
    QString errorText = "";
};

#endif // UI_CONTROLLER_H
