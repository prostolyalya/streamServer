#include "thread_pool.h"

ThreadPool* ThreadPool::instance = new ThreadPool();

ThreadPool::ThreadPool(QObject *parent)
    :QObject(parent)
{
}

ThreadPool* ThreadPool::getInstance()
{
    return instance;
}

// void ThreadPool::addToThread(std::function<void()> fun)
//{
//    instance->pool->start(fun);
//    qDebug() << instance->pool->activeThreadCount();
//}

ThreadPool::~ThreadPool()
{
    for (auto& thread : pool)
    {
        thread->quit();
        thread->wait();
    }
}

QThread* ThreadPool::addToThread(QObject* object)
{
    QThread* thread = new QThread();
    connect(thread, &QThread::finished, object, &QObject::deleteLater);
    instance->pool.insert(thread);
    object->moveToThread(thread);
    thread->start();
    return thread;
}
