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
    unsigned int size_;
    mutex mutex_;
    condition_variable cdvr_;

public:
    CirQueue( size_t cap = 10 ):cap_(cap), head(0), tail(0) ,size_(0), mutex_(), cdvr_()
    {
        arr_ = new T[cap];
    }

    ~CirQueue()
    {
        delete arr_;
    }

    void push( const T rhs ) noexcept
    {
        lock_guard<mutex> lock(mutex_);

        if( Full() )
        {
            cerr << " Over the capacity of CirQueue! " << endl;
            return;
        }    

        size_++;
        arr_[ tail ] = rhs;
        tail = ((tail+1) % cap_);

        cdvr_.notify_one();
    }

    void pop() noexcept
    {
        unique_lock<mutex> lock(mutex_);

        cdvr_.wait( lock, [this]{ return !this->empty(); });

        size_--;
        head = (head + 1) % cap_;

    }

    bool empty()
    {
        lock_guard<mutex> lock(mutex_);
        return size_ == 0;
    }

    size_t capacity()
    {
        lock_guard<mutex> lock(mutex_);
        return cap_;
    }

    bool Full()
    {
        lock_guard<mutex> lock(mutex_);
        return size_ == cap_;
    }

    T front()
    {
        lock_guard<mutex> lock(mutex_);

        if( this->empty() )
        {
            cerr << " queue is empty!";
            return static_cast<T>(NULL);
        }
        
        return arr_[head];
    }
};


void queue_test()
{
    CirQueue<int> queue(3);
    queue.push(1);
    cout<< queue.front();
    queue.push(2);
    queue.push(3);
    queue.pop();
    cout<< queue.front();
    queue.push(4);
}

#endif