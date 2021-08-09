#pragma once
#include<iostream>
#include<mutex>
#include<condition_variable>
using namespace std;

template<typename T>
class BlockingQueue{
public:
	BlockingQueue(int cap):mutex_(),cdvar_(),capactiy(cap),head(0),tail(0) {
		arr_ = new T[cap];
	}

	bool empty() const{ 
		lock_guard<mutex> lock(mutex_);
		return head == tail;
	}

	//push的时候 加入就好了
	void push(const T& rhs) {
		lock_guard<mutex> lock(mutex_);
		//满了之后，业务应该有拒绝的措施
		if ((tail + 1) % capacity == head) {
			return false;
		}
		arr_[(tail = (tail + 1) % capacity))] = rhs;

		cdvar_.notify_all();
	}

	void pop() {
		lock_guard<mutex> lock(mutex_);
		
		cdvar_.wait(lock, [this] {return !this->empty(); });
		//满了之后，业务应该有拒绝的措施
        ////wait() 条件变量类对象的成员函数，用来等一个东西
			//如果第二个参数的lambda表达式返回 true , 那么wait()最接返回
			//如果第二个参数的lambda表达式返回 false ，那么wait()将解锁互斥量，并阻塞到本行
			//阻塞到其他某个线程调用notify_one()成员函数为止
			//如果wait()没有第二个参数 varible.wait(unique) ;那么就和第二个参数lambda表达式返回false效果一样
			//当其他线程用notify_one()将本wait(原来是阻塞)的状态唤醒后，wait()会不断的尝试重新获取互斥量锁 
			//如果获取不到，那么就会卡在wait()这里等着，如果获取到了，wait()就继续执行上锁，如果wait()有第二个参数lambda表达式，如果表达式为

        head = (head + 1) % capacity;
	}

	T front() const {
		lock_guard<mutex> lock(mutex_);
		return arr_[head];
	}

	int capacity() const{
		return capacity;
	}
private:
	T* arr_;
	int head;
	int tail;
	int capacity;
	mutex mutex_;
	condition_variable cdvar_;
};

