#ifndef _THREADPRACTICE_H_
#define _THREADPRACTICE_H_

#include<iostream>
#include<thread>
#include<functional>
#include<mutex>
#include<condition_variable>

using namespace std;


void printNumber(int i)
{
    cout << i;
}

class ZeroEvenOdd
{
private:
    int n;
    bool ze;
    bool other;
    condition_variable cv;
    mutex mtx;
public:
    ZeroEvenOdd(int m) : ze(true), other(true), n(m), cv(), mtx() //true代表可以打印
    {
        
    }

    void printZero(function<void(int)> printNumber)
    {
        for(int i = 0; i < n; ++i)
        {
            unique_lock<mutex> lock(mtx);
            //释放锁，然后阻塞,如果zero没有打印，就开始打印
            cv.wait(lock, [this]{ return this->ze; });  
            printNumber(0);
            ze = false;
            cv.notify_all();
        }
    }

    void printOdd(function<void(int)> printNumber)
    {
        for(int i = 1; i <= n; ++i)
        {
            if(i%2 == 0)  //等于偶数的时候就返回
            {
                continue;
            }
            unique_lock<mutex> lock(mtx);
            //释放锁，然后阻塞，如果zero打印了。就会触发。
            cv.wait(lock, [this]{ return !this->ze && this->other; });
            printNumber(i);
            this->ze = true;
            this->other = false;
            cv.notify_all();
        }
    }


    void printEven(function<void(int)> printNumber)
    {
        for(int i = 2; i <= n; ++i)
        {
            if(i%2 != 0)  //等于偶数的时候开始竞争锁。
            {
                continue;
            }
            unique_lock<mutex> lock(mtx);
            //释放锁，然后阻塞，如果zero打印了，odd打印过了。就会触发。
            cv.wait(lock, [this]{ return !this->ze && !this->other; });
            printNumber(i);
            this->ze = true;
            this->other = true;
            cv.notify_all();
        }
    }


};



//cppreference  introduce bind() 

//template< class F, class... Args >
//bind( F&& f, Args&&... args );

//The function template bind generates a forwarding call wrapper for f. 
//Calling this wrapper is equivalent to invoking f with some of its arguments bound to args.


/*
    int n = 7;
    // (_1 and _2 are from std::placeholders, and represent future
    // arguments that will be passed to f1)
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
                    // makes a call to f(2, 42, 1, n, 7)
*/

int main(int argc, char** argv)
{
    int n = 0;
    cin >> n;
    ZeroEvenOdd zeo(n);
    thread th1 = thread(bind(&ZeroEvenOdd::printZero, &zeo, placeholders::_1), printNumber);
    thread th2 = thread(bind(&ZeroEvenOdd::printOdd, &zeo, placeholders::_1), printNumber);
    thread th3 = thread(bind(&ZeroEvenOdd::printEven, &zeo, placeholders::_1), printNumber);
    th1.join();
    th2.join();
    th3.join();

    return 0;
}



#endif