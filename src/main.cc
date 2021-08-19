#include<iostream>
//#include"Singleton.h"
//#include "ConsistentHashCircle.h"
#include "hashMap.h"
//#include "HashFunction.hpp"
using namespace std;

int main( )
{

    HashMap<int,string> hashMap;
    hashMap.push(1,"1");
    hashMap.push(2,"2");
    hashMap.push(3,"3");
    cout << hashMap.get(1) << endl;
    cout << hashMap.get(2) << endl;
    cout << hashMap.get(3) << endl;
    return 0;
}


//HashFunction* md5 = new MD5HashFunction();
    //cout << md5->getHashValue("127.0.0.18000") << endl;