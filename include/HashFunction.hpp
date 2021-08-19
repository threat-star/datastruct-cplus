#ifndef _HASH_FUNCTION_HPP_
#define _HASH_FUNCTION_HPP_

#include<iostream>
#include<cstring>
#include<openssl/md5.h>
#include<atomic>
#include<mutex>

//使用单例模式 来获取hashfunction

class HashFunction
{
public:
    virtual unsigned long getHashValue(const std::string& key) = 0;
};


class MD5HashFunction: public HashFunction
{
public:
    virtual unsigned long getHashValue(const std::string& key);
};


unsigned long MD5HashFunction::getHashValue(const std::string& key)
{
    unsigned long hashValue = 0;
    unsigned char md5Value[16];
    bzero( md5Value, sizeof(md5Value) );
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, key.c_str(), strlen(key.c_str()));
    MD5_Final(md5Value, &md5);

    for( int i=0; i<4; ++i )
    {
        //每四个字节 进行一次组合
        hashValue +=
        ((long)(md5Value[i*4 + 3]&0xff) << 24) |
        ((long)(md5Value[i*4 + 2]&0xff) << 16) |
        ((long)(md5Value[i*4 + 1]&0xff) << 8 ) |
        ((long)(md5Value[i*4 + 0]&0xff) << 0 ); 
        // hashValue +=
        // ((long)(md5Value[i*4+3]&0xff) << 24) |
        // ((long)(md5Value[i*4+2]&0xff) << 16) |
        // ((long)(md5Value[i*4+1]&0xff) << 8)  |
        // ((long)(md5Value[i*4+0]&0xff) << 0);
    }

    return hashValue;
}


class HashFunctionSingleton
{
public:
    static HashFunction* getInstance();
private:
    HashFunctionSingleton(){}
    HashFunctionSingleton(const HashFunctionSingleton&){}
    static std::atomic<HashFunction*> m_hashfuntion;
    static std::mutex m_mutex;
};

std::atomic<HashFunction*> HashFunctionSingleton::m_hashfuntion;
std::mutex HashFunctionSingleton::m_mutex;

HashFunction* HashFunctionSingleton::getInstance()
{
    HashFunction* tmp = m_hashfuntion.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if(tmp == nullptr)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_hashfuntion.load(std::memory_order_relaxed);
        if( tmp == nullptr )
        {
            tmp = new MD5HashFunction;
            std::atomic_thread_fence(std::memory_order_release);
            m_hashfuntion.store(tmp);
        }
    }
    return tmp;
}



#endif