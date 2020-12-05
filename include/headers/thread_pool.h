#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#pragma once
#include "boost/asio.hpp"
#include "boost/thread.hpp"
#include <vector>
#include <thread>

class ThreadPool
{
    ThreadPool();
//    boost::asio::thread_poll poll;
public:
    bool addToThread();

private:
    std::vector<std::thread> threads;
};

#endif // THREAD_POOL_H
