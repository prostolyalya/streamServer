#include "thread_pool.h"
#include <iostream>

ThreadPool::ThreadPool()
{
    std::cout << &std::thread::hardware_concurrency << std::endl;
}
