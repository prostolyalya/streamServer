#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#pragma once

#include <thread>
#include <QThreadPool>
class ThreadPool
{

public:
    ThreadPool();
    void addToThread(std::function<void()> fun);
    static ThreadPool *instance;
    static ThreadPool *getInstance();

private:
    QThreadPool *pool = nullptr;
};

#endif // THREAD_POOL_H
