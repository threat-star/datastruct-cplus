#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <iostream>
#include <list>
#include <vector>
#include "HashFunction.hpp"

template<class K, class V>
class HashMap
{
public:
    HashMap();
    HashMap( int capacity );
    ~HashMap();
    void push(const K& key,const V& value);
    V get(const K& key);
private:
    //void rehash();  //渐进式hash
    std::vector<std::list<std::pair<K,V>>*> m_arr;
    size_t m_size;
    size_t m_capacity;
};

template<class K, class V>
HashMap<K,V>::HashMap():m_capacity(100), m_size(0)
{
    m_arr.reserve(m_capacity);
}


template<class K, class V>
HashMap<K,V>::HashMap( int capacity ):m_capacity(capacity), m_size(0)
{
    m_arr.reserve(capacity);
}

template<class K, class V>
HashMap<K,V>::~HashMap()
{
    for( int i=0; i<m_arr.size(); ++i )
    {
        delete m_arr[i];
    }
}

template<class K, class V>
void HashMap<K,V>::push(const K& key,const V& value)
{
    unsigned long hashKey = HashFunctionSingleton::getInstance()->getHashValue( std::to_string((size_t)&key) );
    if( m_arr[hashKey % m_capacity] == nullptr )
    {
        m_arr[hashKey % m_capacity] = new std::list< std::pair<K,V> >;
    }
    m_arr[hashKey % m_capacity]->push_back( make_pair(key, value) );
    ++m_size;
}

template<class K, class V>
V HashMap<K,V>::get(const K& key)
{
    unsigned long hashKey = HashFunctionSingleton::getInstance()->getHashValue( std::to_string((size_t)&key) );
    if( m_arr[hashKey % m_capacity] == nullptr )
    {
        return NULL; 
    }

    auto begin = m_arr[hashKey % m_capacity]->begin();
    auto end = m_arr[hashKey % m_capacity]->end();

    for( ;begin != end; begin++ )  //hash值相等的时候，对比key值
    {
        if( key == begin->first )
        {
            return begin->second;
        }
    }

    return NULL;
}



#endif