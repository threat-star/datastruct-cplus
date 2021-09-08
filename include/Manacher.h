//Copyright (c) 2021 by sumra

#ifndef _MANACHER_H_
#define _MANACHER_H_

#include <iostream>
#include <string>

using namespace std;

string manacher_string(const string &s)
{
    int len = s.size();
    string res;
    int index = 0;
    for (int i = 0; i < 2 * len + 1; ++i)
    {
        res += (i & 1) == 0 ? '#' : s[index++];
    }

    return res;
}

string longestPalindrome(string s) {
    //MANACHER
    //最大回文右边界
    int len = s.size();
    string str = manacher_string(s);
    int *pArr = new int[str.size()];
    int index = -1, pre = -1, max_len = -1, max_index;
    for (int i = 0; i < str.size(); ++i)
    {
        pArr[i] = pre > i ? min(pre - i, pArr[2 * index - i]) : 1;
        //开始扩展最大回文边界
        while (i + pArr[i] < str.size() && i - pArr[i] >= 0) {
            if (str[i + pArr[i]] == str[i - pArr[i]]) {
                pArr[i]++;
            } else {
                break;
            }
        }

        if (i + pArr[i] > pre) {
            pre = i + pArr[i];
            index = i;
        }

        if (max_len < pArr[i]) {
            max_len = pArr[i];
            max_index = i;
        }
    }

    string res;
    // index 为中心， pArr[index]为半径
    for (int i = max_index - pArr[max_index] + 1; i < max_index + pArr[max_index] - 1; ++i) {
        if (str[i] != '#')
            res += str[i];
    }

    delete[] pArr;
    return res;
}

#endif 