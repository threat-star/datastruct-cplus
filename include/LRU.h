#ifndef _LRU_H_
#define _LRU_H_

#include<iostream>
#include<list>
#include<map>

using namespace std;

class LRU
{
private:

    using list_type = list<pair<int, int>>;
    using cache_type = map<int, list<pair<int, int>>::iterator>;

    int m_cap;
    list_type list_;
    cache_type Cache;
public:

    LRU( int capacity = 10 ): m_cap(capacity){}

    int get( int key )
    {
        auto cacheIter = Cache.find(key);
        if( cacheIter == Cache.end() )
        {
            return -1;
        }

        auto value = cacheIter->second->second;
        //放到前面
        list_.erase( cacheIter->second );
        list_.push_front({key, value});
        Cache[key] = list_.begin();

        return value;
    }

    void put( int key, int value )
    {
        auto cacheIter = Cache.find( key );
        if( cacheIter == Cache.end() )  //没有命中
        {
            if( list_.size() == m_cap ) //超出了数量的限制 
            {
                auto tmpKey = list_.back().first;
                Cache.erase( tmpKey );
                list_.pop_back();
            }
        }            
        else
        {
            list_.erase( cacheIter->second );
        }
        list_.push_front({key, value});
        Cache[key] = list_.begin();
    }

    int capacity()
    {
        return m_cap;
    }

    size_t size()
    {
        return list_.size();
    }

};

#endif