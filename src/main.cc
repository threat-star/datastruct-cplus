#include<iostream>
#include<vector>
#include"../include/cirqueue.h"

using namespace std;

    double findMaxAverage(vector<int>& nums) {

        int n = nums.size();
        vector<int> sums = nums;

        for (int i = 1; i < n; ++i) {
            sums[i] = sums[i - 1] + nums[i];
        }

        double res = (double)sums[0];
        for (int i = 1; i < n; ++i) 
        {
            double t = sums[i];
            if (t > res * (i + 1)) 
            {
                res = t / (i + 1);
            }

            for (int j = i - 1; j >= 0; --j) 
            {
                t = sums[i] -  sums[j];
                if ( t > res * (i - j) ) 
                {
                    res = t / (i - j);
                }
            }
        }
        return res;
    }

int main( )
{
    queue_test();
    return 0;
}