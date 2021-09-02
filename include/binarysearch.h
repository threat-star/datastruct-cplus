#ifndef _BINARY_SEARCH_H_
#define _BINARY_SEARCH_H_

#include <iostream>
#include <vector>

int bsearch(std::vector<int> arr, int n, int value) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if(arr[mid] == value) {
            return mid;
        } else if (arr[mid] > value) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}


//变体一 : 查找第一个值等于给定值的元素
int bsearch1(std::vector<int> arr, int n, int value) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (arr[mid] > value) {
            low = mid + 1;
        } else if (arr[mid] < value) {
            high = mid - 1;
        } else {
            if ((mid == 0) || (arr[mid - 1] != value)) return mid;
            else high = mid - 1;
        }
    }

    return -1;
}

//变体二:查找最后-个值等于给定值的元素
int bsearch2(std::vector<int> arr, int n, int value) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (arr[mid] > value) {
            low = mid + 1;
        } else if (arr[mid] < value) {
            high = mid - 1;
        } else {
            if ((mid == n - 1) || (arr[mid + 1] != value)) return mid;
            else low = mid + 1;
        }
    }

    return -1;
}


//变体三:查找第一个大于等于给定值的元素
int bsearch3(std::vector<int> arr, int n, int value) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (arr[mid] >= value) {
            if ((mid == 0) || (arr[mid - 1] < value)) return mid;
            else high = mid + 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

union is_big
{
    short s;
    char c[2];
};

//变体四:查找最后-一个小于等于给定值的元素
int bsearch3(std::vector<int> arr, int n, int value) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + ((high - low) >> 1);
        if (arr[mid] <= value) {
            if ((mid == n - 1) || (arr[mid + 1] > value)) return mid;
            else low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

#endif