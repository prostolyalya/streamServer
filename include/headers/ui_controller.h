#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H
#pragma once
#include <QObject>
#include <qqml.h>

class UiController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uiTextServer READ getTextServer WRITE setTextServer NOTIFY textServerChanged)
public:
    UiController(QObject* parent = nullptr);
    ~UiController();
    void addTextServer(QString text);
    QString getTextServer() const;

    void setTextServer(const QString &value);

signals:
    void textServerChanged();

private:
    QString textServer;
};

#endif // UI_CONTROLLER_H
