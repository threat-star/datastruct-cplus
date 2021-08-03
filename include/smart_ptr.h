#ifndef _SMART_PTR_
#define _SMART_PTR_

#include<iostream>
#include<mutex>
using namespace std;

mutex mu;
//先定义引用计数
class shared_count 
{
public:
	shared_count():count_(1) {}
	void add_count() {
		//lock_guard<mutex> lock(mu);
		++count_;
	}
	long reduce_count() {
		//lock_guard<mutex> lock(mu);
		return --count_;
	}
	long get_count() const noexcept { 
		return count_; 
	}
private:
	long count_;
};

template<typename T>
class smart_ptr
{

public:
	template<typename U>
	friend class smart_ptr;
	//shared_ptr  是通过拷贝函数来进行共享的；
	//所以构造函数 时值初始化就好；
	explicit smart_ptr(T* ptr) {
		ptr_ = ptr;
		shared_count_ = new shared_count();
	}

	//拷贝构造函数
	smart_ptr(const smart_ptr& other) {
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

	//还要完成可以支持类型转换的 拷贝构造
	template<typename U>
	smart_ptr(const smart_ptr<U>& other) noexcept {
		ptr_ = other.ptr_;
		if (ptr_) {
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_;
		}
	}

    //所有 右值引用都会走该语句。
    //what a move semantics
    //https://stackoverflow.com/questions/3106110/what-is-move-semantics/3109981#3109981
	template<typename U>
	smart_ptr(smart_ptr<U>&& other) noexcept {
		ptr_ = other.ptr_;  //两个不同的 typename类型 就不会访问互相的private；
		if (ptr_) {
			shared_count_ = std::other.shared_count_;  //引用计数为0的时候才会进行注销；
			other.ptr_ = nullptr;
		}
	}


	template<typename U>
	smart_ptr(const smart_ptr<U>& other, T* ptr) noexcept 
	{ 
		ptr_ = ptr; 
		if (ptr_) 
		{ 
			other.shared_count_->add_count();
			shared_count_ = other.shared_count_; 
		} 
	} 


	//https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom/3279550#3279550
	// What is the copy-and-swap idiom
    // 防止自我赋值  + 函数中抛出异常（编写try and catch ，影响效率 ）
	smart_ptr<T>& operator=( smart_ptr<T> rhs ) noexcept 
	{ 
		rhs.swap(*this); 
		return *this; 
	}

	~smart_ptr() {
		if (ptr_ && shared_count_->reduce_count() == 0) {
			delete ptr_;
			delete shared_count_;
		}
	}

	long use_count() const noexcept { 
		if (ptr_) 
		{ 
			return shared_count_->get_count();
		} 
		else 
		{ 
			return 0; 
		}
	}

	void swap(smart_ptr& rhs) noexcept{ 
		using std::swap; 
		swap(ptr_, rhs.ptr_); 
		swap(shared_count_, rhs.shared_count_); 
	}

	T& operator*() const noexcept 
	{ return *ptr_; }

	T* operator->() const noexcept 
	{ return ptr_; }

	operator bool() const noexcept 
	{ return ptr_; }

private:
	T* ptr_;
	shared_count* shared_count_;
};

template <typename T> 
void swap(smart_ptr<T>& lhs, smart_ptr<T>& rhs) noexcept 
{ 
	lhs.swap(rhs);
}



#endif