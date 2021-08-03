#pragma once
#include<iostream>
#include<vector>

using namespace std;
//heap
template<class T>
struct Less {
	bool operator()(const T& a, const T& b) {
		return a < b;
	}
};

template<class T>
struct Greater {
	bool operator()(const T& a, const T& b) {
		return a > b;
	}
};

template<class T, class Compare = Less<T>>
class Heap {
public:
	Heap() {}
	Heap(T* arr, int len) {
		if (len < 0)
		{
			cout << "Aguments had no elements";
			return;
		}

		//重置vector空间
		_v.reserve(len);
		for (int i = 0; i < len; ++i) {
			_v.push_back(arr[i]);
		}

		//建堆/找到最后一个非叶节点
		for (int i = _v.size() / 2 - 1; i >= 0; --i) {
			AdjustDown(i);
		}
	}

	void AdjustDown(int root) {
		Compare com;
		int parent = root;
		int child = 2 * parent + 1;
		while (child < _v.size()) {
			if (child + 1 < _v.size() && _v[child] < _v[child + 1])
			{
				child++;
			}
			if (com(_v[child], _v[parent])) {
				swap(_v[child], _v[parent]);
				parent = child;
				child = 2 * parent + 1;
			}
			else {
				break;
			}
		}
	}

	void AdjustUp(int root) {
		Compare com;
		int child = root;
		int parent = (child - 1) / 2;
		while (parent >= 0) {
			if (com(_v[child], _v[parent])) {
				swap(_v[child], _v[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else {
				break;
			}
		}
	}

	void push(const T& tmp) {
		_v.push_back(tmp);
		AdjustUp(_v.size() - 1);
	}

	void pop() {
		swap(_v[0], _v[_v.size() - 1]);
		_v.pop_back();
		AdjustDown(0);
	}

	bool empty() {
		return _v.empty();
	}

	T& top() {
		if (_v.size() != 0) {
			return _v[0];
		}
		return NULL;
	}
    
	size_t size() {
		return _v.size();
	}

	void Print() {
		for (auto i : _v) {
			cout << i << " ";
		}
	}
private:
	vector<T> _v;
};
