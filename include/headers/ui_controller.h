#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H
#pragma once

#include <QObject>

class UiController : public QObject
{
    Q_OBJECT
public:
    UiController(QObject* parent = nullptr);
    ~UiController();
    void startLogin(QString path);
signals:
    void login(QString login, QString pass, bool reg);
public slots:
    void addText(QString text);
    void loginComplete(bool complete, QString path);
};

#endif // UI_CONTROLLER_H
