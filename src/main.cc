#include <iostream>
//#include"Singleton.h"
//#include "ConsistentHashCircle.h"
//#include "parse.h"
//#include "HashFunction.hpp"

#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define __tolower(c) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define __toupper(c) ((c >= 'A' && c <= 'Z') ? (c & ~0x20) : c)

vector<vector<int>> parseString(const char &ch)
{
    string line;
    vector<vector<int>> res;
    while (getline(cin, line) && line != "")
    {
        vector<int> nums;
        stringstream ss(line);
        while (getline(ss, line, ch))
        {
            int num = stoi(line);
            nums.push_back(num);
        }

        res.push_back(nums);
    }

    return res;
}

int find_reapt_num(const vector<int>& arr)
{
    int sum = 0;
    int n = arr.size();
    for(int i = 1; i <= 1000; ++i){
        sum ^= i;       //异或会得到1和1000的数的异或结果  1^2...^1000
        sum ^= arr[i-1];      // (1^2...^1000)  ^ (1^2...^1000) ^ target
    }

    return sum ^ arr[1000];
}

int main()
{
    vector<int> vec(1001, 0);
    for(int i = 1; i <= 1000; ++i){
        vec[i - 1] = i;
    }

    vec[1000] = (random() % 1000) + 1;
    cout << find_reapt_num(vec) << endl;

    // vector<char> vec{'1', ' ', '2', ' ', '3', ' ', '4'};
    // for (auto i : vec)
    // {
    //     cout << i;
    // }
    // cout << endl;

    // for (auto it = vec.begin(); it != vec.end();)
    // {
    //     if (*it == ' ')
    //     {
    //         it = vec.erase(it);
    //     }
    //     else
    //     {
    //         ++it;
    //     }
    // }

    // for (auto i : vec)
    // {
    //     cout << i;
    // }
    // cout << endl;


    // vec.erase(remove(vec.begin(),vec.end(), ' '), vec.end());
    // cout << vec.size() << endl;
    // for (auto i : vec)
    // {
    //     cout << i;
    // }
    // cout << endl;

    return 0;
}

//HashFunction* md5 = new MD5HashFunction();
//cout << md5->getHashValue("127.0.0.18000") << endl;

