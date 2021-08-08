#ifndef _BIT_MAP_H_
#define _BIT_MAP_H_

#include<iostream>
#include<vector>

using namespace std;

class bitmap
{
private:
    vector<size_t> _a;
    size_t _size;
public:

    bitmap( size_t size = 100 ):_size(size)
    {
        _a.reserve( ( size >> 5 ) + 1 );  // max/32 + 1
    }   

    void Set( size_t x )
    {
        if( x > _size )
        {
            cerr << " Over the capacity of bitmap! "<<endl;
            return;
        }
        size_t index = x >> 5;
        size_t num = x % 32;
        _a[index] |= ( 1 << num );
    }

    void Reset(size_t x)
    {
        if( x > _size )
        {
            cerr << " Over the capacity of bitmap! "<<endl;
            return;
        }
        //size_t index = x / 32;
        size_t index = x >> 5;
        size_t num = x % 32;

        //该位存在则将该位二进制置为0
        _a[index] &= ~(1 << num);
    }

    bool Test(size_t x)
    {
        if( x > _size )
        {
            cerr << " Over the capacity of bitmap! "<<endl;
            return;
        }
        //size_t index = x / 32;
        size_t index = x >> 5;
        size_t num = x % 32;
        if (_a[index] & (1 << num))
        {
            return true;
        }
        return false;
    }

    void Resize(size_t size)
    {
        _a.resize(size);

    }

};


// 1千万 个 int --> 10000000/8 =   

#endif