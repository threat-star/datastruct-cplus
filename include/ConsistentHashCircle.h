#ifndef _CONSISTENTHASHCIRCLE_H_
#define _CONSISTENTHASHCIRCLE_H_

#include<iostream>
#include<openssl/md5.h>
#include<cstring>
#include<map>

#define LOG(fmt, para...) do{printf(fmt"\r", ##para);}while(0)
#define LOG_FUNC_TRACE() LOG("[Line:%d][Function:%s]\n", __LINE__, __FUNCTION__)

class HashFunction
{
public:
    virtual long getHashValue(const std::string& str) = 0;
};

class MD5HashFunction
{
public:
    virtual long getHashValue(const std::string& str);
};

long MD5HashFunction::getHashValue(const std::string& str)
{
    LOG_FUNC_TRACE();
    long hashValue = 0;
    unsigned char hash[16];
    bzero(hash, sizeof(hash));
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, str.c_str(), strlen(str.c_str()));
    MD5_Final(hash, &md5);

    for( int i=0; i<4; ++i)
    {
        hashValue +=
        ((long)(hash[i*4+3]&0xff) << 24) |
        ((long)(hash[i*4+2]&0xff) << 16) |
        ((long)(hash[i*4+1]&0xff) << 8)  |
        ((long)(hash[i*4+0]&0xff) << 0);
    }

    return hashValue;
}

class PhysicalNode
{
public:
    PhysicalNode();
    PhysicalNode(int cnt, const std::string& ip, unsigned short port);
    ~PhysicalNode();
    void setPhysicalNode(const std::string& ip, unsigned short port);
    std::string getIp();
    unsigned short getPort();
    int getVirtualNodeCnt();
private:
    int m_cnt;             //虚拟节点的数量
    std::string m_ip;
    unsigned short m_port;
};

class VirtualNode
{
public:
    VirtualNode();
    VirtualNode(PhysicalNode* father); \
    ~VirtualNode();
    PhysicalNode* getFatherPhysicalNode();
    void setHash(long hash);
    long getHash();
    void VirtualNode::setVirtualNode(PhysicalNode* father); 
private:
    PhysicalNode* m_father;
    unsigned long m_hashValue;    //节点的hash值
};

class ConsistentHashCircle
{
public:
    ConsistentHashCircle() = delete;
    ConsistentHashCircle(HashFunction* fun);
    ~ConsistentHashCircle();
    void setHashFunction(HashFunction* fun);
    int addVirtualNode(PhysicalNode* node);
    PhysicalNode* getPhysicalNode(const std::string& sock);
    int removeVirtualNode(PhysicalNode* node);
private:
    HashFunction* m_fun;
    unsigned int m_virtualNodeCnt;
    std::map<unsigned long, VirtualNode*> m_virtualNodeMap;
};

// ConsistentHashCircle::ConsistentHashCircle()
// {
    
// }

ConsistentHashCircle::ConsistentHashCircle(HashFunction* fun):m_fun(fun),m_virtualNodeCnt(0)
{

}

ConsistentHashCircle::~ConsistentHashCircle()
{
    m_virtualNodeMap.clear();
}

void ConsistentHashCircle::setHashFunction(HashFunction* fun)
{
    m_fun = fun;
}

int ConsistentHashCircle::addVirtualNode(PhysicalNode* node)
{
    LOG_FUNC_TRACE();
    if(!node || node->getVirtualNodeCnt() <= 0)
    {
        std::cerr << "";
        return -1;
    }

    std::string sock = node->getIp() + std::to_string(node->getPort());
    std::string tmp = sock;
    VirtualNode* virtualNode;
    int n = node->getVirtualNodeCnt();
    for( int i = 0; i<n; ++i )
    {
        tmp = tmp + std::to_string(i);
        long hashValue = this->m_fun->getHashValue(tmp);
        auto it = this->m_virtualNodeMap.find(hashValue);
        if( it == this->m_virtualNodeMap.end() )
        {
            virtualNode = new VirtualNode(node);
            virtualNode->setHash(hashValue);
            this->m_virtualNodeCnt++;
            this->m_virtualNodeMap.insert( std::make_pair(hashValue, virtualNode) );
        }
        else
        {
            LOG_FUNC_TRACE();
            std::cerr << "";
            return -1;
        }
        tmp = sock;
    }

    LOG_FUNC_TRACE();
    return 0;
}

PhysicalNode* ConsistentHashCircle::getPhysicalNode(const std::string& sock)
{
    unsigned long hashValue = this->m_fun->getHashValue(sock);

    auto iter = this->m_virtualNodeMap.lower_bound(hashValue);    //取第一个比他大的iter
    if (iter == m_virtualNodeMap.end()) 
    {
        iter = m_virtualNodeMap.begin();
    }
    VirtualNode* res = iter->second;
    
    return res==nullptr ? nullptr : res->getFatherPhysicalNode();
}

int ConsistentHashCircle::removeVirtualNode(PhysicalNode* node)
{
    LOG_FUNC_TRACE();
    if (!node) return -1;
    std::string sock = node->getIp() + std::to_string(node->getPort());
    std::string tmp = sock;
    unsigned long hashValue = 0;
    for (int i=0; i < node->getVirtualNodeCnt(); ++i) {
        tmp += std::to_string(i);
        hashValue = m_fun->getHashValue(tmp);
        if(m_virtualNodeMap.find(hashValue) == m_virtualNodeMap.end())
        {
            return -1;
        }

        m_virtualNodeMap.erase(hashValue);
        m_virtualNodeCnt --; 
        tmp = sock;
    }

    LOG_FUNC_TRACE();
    return 0;
}


PhysicalNode::PhysicalNode():m_cnt(0) {}

PhysicalNode::PhysicalNode(int cnt, const std::string& ip, unsigned short port):
    m_cnt(cnt),m_ip(ip), m_port(port) {}

void PhysicalNode::setPhysicalNode(const std::string& ip, unsigned short port) {
    this->m_ip = ip;
    this->m_port = port;
}

int PhysicalNode::getVirtualNodeCnt() {
    return m_cnt;
}

unsigned short PhysicalNode::getPort() {
    return m_port;
}

std::string PhysicalNode::getIp() {
    return m_ip;
}

VirtualNode::VirtualNode() {

}

VirtualNode::VirtualNode(PhysicalNode* father) {
    this->m_hashValue = -1;
    this->m_father = father;
}

void VirtualNode::setVirtualNode(PhysicalNode* father) {
    this->m_father = father;
}

PhysicalNode* VirtualNode::getFatherPhysicalNode() {
    return this->m_father;
}

void VirtualNode::setHash(long hash) {
    this->m_hashValue = hash;
}

long VirtualNode::getHash() {
    return this->m_hashValue;
}



#endif