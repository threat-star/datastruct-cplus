#include<iostream>
#include"LRU.h"

using namespace std;

int main( int argc, char*argv[] )
{
    LRU cache(3);
    cache.put(1,1);
    cout << cache.get(1) << endl;
    cache.put(2,2);
    cache.put(3,3);
    cache.put(4,4);
    cout<< cache.get(1) << " " << cache.get(2) << endl;

    return 0;
}