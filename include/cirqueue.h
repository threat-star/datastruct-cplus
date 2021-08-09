#ifndef _CIRQUEUE_H_
#define _CIRQUEUE_H_

#include<iostream>
#include<mutex>
#include<condition_variable>
#include<gtest/gtest.h>

using namespace std;

template<class T>
class CirQueue
{
private: 
    int* arr_;
    unsigned int cap_;
    unsigned int head;
    unsigned int tail;
    mutex mutex_;
    condition_variable cdvr_;

public:
    CirQueue( size_t cap = 10 ):cap_(cap), head(0), tail(0), mutex_()
    {
        arr_ = new T[size];
    }

    ~CirQueue()
    {
        delete arr_;
    }

    void push( cont T& rhs ) noexcept
    {
        lock_guard<mutex> lock(mutex_);

        if( ((tail+1) % cap_) == head )
        {
            cerr << " Over the capacity of CirQueue! " << endl;
            return;
        }    

        arr_[ tail = ((tail+1) % cap_) ] = rhs;

        cdvr_.notify_one();
    }

    void pop() noexcept
    {
        lock_guard<mutex> lock(mutex_);

        cdvr_.wait( lock, [this]{ return !this->empty(); });

        head = (head + 1) % cap_;
    }

    bool empty()
    {
        lock_guard<mutex> lock(mutex_);
        return head == tail;
    }

    size_t capacity()
    {
        return cap_;
    }
};



#endif