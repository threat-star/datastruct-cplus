#include <iostream>
#include "mysort.h"
//#include <gtest/gtest.h>

using namespace std;

// TEST(quickSort, first_test)
// {
    
// }

int main()
{
    vector<int> vec = {4, 6, 7, 2, 1, 9, 5, 3, 8, 10};
    quickSort(vec, 0, vec.size()-1);
    for(auto& i : vec){
        cout << i << " ";
    }
}