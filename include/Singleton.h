#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include<iostream>
#include<atomic>
#include<mutex>

class Singleton
{
public:
    static Singleton* getInstance();
private:
    Singleton(){}
    Singleton(const Singleton& other){}
    static std::atomic<Singleton*> m_instance;
    static std::mutex m_mutex;
};

std::atomic<Singleton*> Singleton::m_instance;
std::mutex Singleton::m_mutex;

Singleton* Singleton::getInstance()
{
    Singleton* tmp = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence( std::memory_order_acquire );
    if( tmp == nullptr )
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
        if( tmp == nullptr )
        {
            m_instance = new Singleton();
            std::atomic_thread_fence(std::memory_order_release);
            m_instance.store(tmp);
        }
    }
    return tmp;
}


#endif