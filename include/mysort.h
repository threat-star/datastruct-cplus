/*
 * @Author: sumra
 * @Date: 2021-09-16 21:36:18
 * @LastEditTime: 2021-09-16 21:36:34
 * @LastEditors: sumra
 * @Description: In User Settings Edit
 * @FilePath: /datastruct/include/mysort.h
 */
#pragma once

#ifndef SORT_H
#define SORT_H
#include<iostream>
#include<vector>
#include<iterator>

using namespace std;

void swap(int* a, int* b);
void bubbleSort(vector<int>& vec);
void print(vector<int>vec);
void insertSort(vector<int>& vec);
void shellSort(vector<int>& vec);
void quickSort(vector<int>& vec, int s, int e);
void heapSort(int* arr,int len);
void memerySort(vector<int>& vec);
void countingSort(vector<int>& vec);
void RadixSort(vector<int>& vec);


void swap(int* a, int* b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void bubbleSort(vector<int>& vec) {   //将最大的数 放到最后面。
	for (int i = vec.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (vec[j] > vec[j + 1]) {
				swap(&vec[j], &vec[j + 1]);
			}
		}
	}
}

void selectSort(vector<int>& vec) {   // 从前向后，  有比当前数小的 ，都进行交换。
	for (int i = 0; i < vec.size();i++) {
		for (int j = i+1; j < vec.size(); j++) {
			if (vec[i]>vec[j]) {
				swap(&vec[i], &vec[j]);
			}
		}
	}
}

void shell(vector<int>& vec,int gap) {
	int tmp,k;
	for (int i = 0; i < gap;i++) {
		for (int j = gap; j < vec.size(); j+=gap) {
			tmp = vec[j]; 
			for (k = j - gap; k >= 0;k-=gap) {
				if (tmp<vec[k]) {
					vec[k + gap] = vec[k];
				}
				else {
					break;
				}
			}
			vec[k + gap] = tmp;
		}
	}
}

void shellSort(vector<int>& vec) {
	for (int gap = vec.size() / 2; gap >= 1;gap/=2) {
		shell(vec,gap);
	}
}


void insertSort(vector<int>& vec) {   //从第二个位置开始找，找到第一个比当前数小的。
	int tmp, j;   
	for (int i = 1; i < vec.size();i++) {  
		tmp = vec[i];
		for ( j = i - 1; j >= 0; j-- ) {
			if ( tmp < vec[j] ) {
				//break;
				vec[j + 1] = vec[j];
			}
			else {
				break;
			}
		}
		vec[j + 1] = tmp;
	}
}

void quickSort(vector<int>& vec,int s,int e) {
	if (s >= e)
		return;
	int start = s;
	int end = e;
	int tmp = vec[start];
	while (start<end) {
		while (start < end && vec[end] > tmp) {
			end--;
		}
		
		if (start < end)
			vec[start++] = vec[end];

		while (start < end && vec[start] < tmp)
			start++;

		if (start < end)
			vec[end--] = vec[start];
	}
	
	vec[start] = tmp;
	quickSort(vec, s, end-1);
	quickSort(vec, start+1, e);
}


void AdjustDown(int* arr, int start, int end) {

	int parent = start;
	int child = 2 * parent + 1;
	while (child <= end) {
		if (child + 1 <= end && arr[child + 1] > arr[child]) {
			child++;
		}

		if (arr[parent] < arr[child]) {
			swap(arr[parent], arr[child]);
			parent = child; 
			child = 2 * parent + 1;
		} else {
			break;
		}

	}
}


void heapSort(int* arr,int len) {

	for (int i = len / 2 - 1; i >= 0; i--) {
		AdjustDown(arr, i, len-1);
	}

	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		AdjustDown(arr, 0, i - 1);
	}

}

void print(vector<int>vec) {

    copy( vec.begin(), vec.end(), ostream_iterator<int>( cout, " " ) );
    cout<<endl;
}

#endif // !_SORT_H_



