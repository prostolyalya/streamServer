#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#pragma once
#include <vector>
#include <thread>
class ThreadPool
{
    ThreadPool();

public:
    bool addToThread();

private:
    std::vector<std::thread> threads;
};

#endif // THREAD_POOL_H
