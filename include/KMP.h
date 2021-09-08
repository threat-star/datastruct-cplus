//Copyright (c) 2021 by sumra

#ifndef _KMP_H_
#define _KMP_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> get_next(string match) {
    if (match.length() == 1) {
        return vector<int>(1, -1);
    }

    vector<int> vec(match.length());
    vec[0] = -1;
    vec[1] = 0;
    int pos = 2, cn = 0;
    while (pos < match.length()) {
        if (match[pos - 1] == match[cn]) {
            vec[pos++] = ++cn;
        } else if (cn > 0) {
            cn = vec[cn];
        } else {
            vec[pos++] = 0;
        }
    } 

    return vec;
}

int get_index(string str, string match) {
    if (str.length() < match.length() || str.length() < 1 || match.length() < 1) {
        return -1;
    }

    vector<int> next = get_next(match);
    int i = 0, j = 0;
    while (i < str.length() && j < match.length()) {
        if (str[i] == match[j]) {
            i++;
            j++;
        } else {
            if (next[j] == -1) {
                i++;
            } else {
                j = next[j];
            }
        }
    }

    return j == match.length() ? i - j : -1; 
}



#endif