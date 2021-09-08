#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int lengthOfLongestSubstring(string s)
{
    if (s.size() == 0)
    {
        return 0;
    }

    map<char, int> ma;
    int len = s.size();
    int pre = -1, max = -1;
    for (int i = 0; i < len; ++i)
    {
        auto iter = ma.find(s[i]);
        if (iter != ma.end())
        {
            pre = pre > iter->second ? pre : iter->second;
        }

        max = (i - pre) > max ? (i - pre) : max;
        ma[s[i]] = i;
    }

    return max;
}

string manacher_string(const string &s)
{
    int len = s.size();
    string res;
    int index = 0;
    for (int i = 0; i < 2 * len + 1; ++i)
    {
        res += (i & 1) == 0 ? '#' : s[index++];
    }

    cout << res;
    return res;
}

string longestPalindrome(string s)
{
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
        while (i + pArr[i] < str.size() && i - pArr[i] >= 0)
        {
            if (str[i + pArr[i]] == str[i - pArr[i]])
            {
                pArr[i]++;
            }
            else
            {
                break;
            }
        }

        if (i + pArr[i] > pre)
        {
            pre = i + pArr[i];
            index = i;
        }

        if (max_len < pArr[i])
        {
            max_len = pArr[i];
            max_index = i;
        }
    }

    string res;
    // index 为中心， pArr[index]为半径
    for (int i = max_index - pArr[max_index] + 1; i < max_index + pArr[max_index] - 1; ++i)
    {
        if (str[i] != '#')
            res += str[i];
    }

    delete[] pArr;
    return res;
}

int max_staisfaction(vector<int> arr)
{
    sort(arr.begin(), arr.end());
    int preSum = 0, res = 0;
    for (int i = arr.size(); i >= 0; --i)
    {
        if (preSum + arr[i] >= 0)
        {
            preSum += arr[i];
            res += preSum;
        }
        else
        {
            break;
        }
    }

    return res;
}

vector<vector<int>> threeSum(vector<int> &nums)
{
    //排序然后 二分查找就可可以了
    sort(nums.begin(), nums.end());
    vector<vector<int>> ret;
    int n = nums.size();

    for (int first = 0; first < n; ++first)
    {
        if (first > 0 && nums[first] == nums[first - 1])
        {
            continue;
        }

        int second = first + 1;
        int third = n - 1;
        int target = -nums[first];
        while (second < third)
        {
            while (second < third && nums[second] == nums[second + 1])
            {
                second++;
            }

            while (second < third && nums[third] == nums[third - 1])
            {
                third--;
            }

            if ((nums[second] + nums[third]) == target)
            {
                ret.push_back({nums[first], nums[second], nums[third]});
                second++;
                third--;
            }
            else if ((nums[second] + nums[third]) > target)
            {
                third--;
            }
            else
            {
                second++;
            }
        }
    }

    return ret;
}

int threeSumClosest(vector<int> &nums, int target)
{
    //set.lower_bound();
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int sum = 1e7;
    auto com = [&](int cur)
    {
        if (abs(cur - target) < abs(sum - target))
            sum = cur;
        
    };

    for (int first = 0; first < n; ++first)
    {
        if (first > 0 && nums[first] == nums[first - 1])
        {
            continue;
        }

        int second = first + 1;
        int third = n - 1;
        while (second < third)
        {
            int cur = nums[first] + nums[second] + nums[third];
            cout << nums[first]<< " "  << nums[second]<< " "  << nums[third] << " " << cur << endl;
            if (cur == target) {
                return target;
            }

            com(cur);

            if (cur > target)
            {
                // 如果和大于 target，移动 c 对应的指针
                    int k0 = third - 1;
                    // 移动到下一个不相等的元素
                    while (second < k0 && nums[k0] == nums[third]) {
                        --k0;
                    }
                    third = k0;

                // // while (third > second && nums[third] == nums[third - 1])
                // //     third--;
                // third--;
            }
            else
            {
                int k0 = second + 1;
                    // 移动到下一个不相等的元素
                    while (k0 < third && nums[k0] == nums[second]) {
                        ++k0;
                    }
                    second = k0;
            //     while (third > second && nums[second] == nums[second - 1])
            //         second++;
                //second++;
            }
        }
    }

    return sum;
}


int main()
{

    //vector<int> vec = {1,2,4,8,16,32,64,128};
    //cout << threeSumClosest(vec, 82);
    // vector<int> vec = {-1, 0, 1, 2, -1, -4};
    // vector<vector<int>> ans = threeSum(vec);
    // for (auto &i : ans)
    // {
    //     for (auto &j : i)
    //     {
    //         cout << j << " ";
    //     }

    //     cout << endl;
    // }

    return 0;
}