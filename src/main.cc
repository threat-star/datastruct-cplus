#include<iostream>
#include "ConsistentHashCircle.h"

using namespace std;

int main( )
{
    HashFunction* md5 = new MD5HashFunction();
    cout << md5->getHashValue("127.0.0.18000") << endl;

    return 0;
}