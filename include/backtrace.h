#include <iostream>
#include <vector>

using namespace std;

bool bracktrace(vector<int> &matchsticks, int target, int index, int *size)
{
    //结束条件
    if (index == matchsticks.size())
    {
        if (size[0] == size[1] && size[1] == size[2] && size[2] == size[3])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //
    for (int i = 0; i < 4; ++i)
    {
        if (target < size[i] + matchsticks[index])
        {
            continue;
        }
        size[i] += matchsticks[index];

        //放到size[i]上继续判断
        if (bracktrace(matchsticks, target, index + 1, size))
        {
            return true;
        }
        //不成功，将结果撤销，试试其他的size。
        size[i] -= matchsticks[index];
    }

    //不能构成正方形
    return false;
}

bool makesquare(vector<int> &matchsticks)
{
    //回溯法，将火柴分成4份。
    int n = matchsticks.size(), sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += matchsticks[i];
    }

    if (sum == 0 || (sum & 3) != 0)
    {
        return false;
    }

    int *size = new int[4];

    bool boolean = bracktrace(matchsticks, sum >> 2, 0, size);
    delete[] size;
    return boolean;
}