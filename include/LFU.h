/*
 * @Author: sumra
 * @Date: 2021-09-16 18:33:46
 * @LastEditTime: 2021-09-16 21:32:52
 * @LastEditors: Please set LastEditors
 * @Description: Implement LFU algorithm
 * @FilePath: /datastruct/include/LFU.h
 */

#ifndef _LFU_H_
#define _LFU_H_

#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

struct Node {
    int key, val, freq;
    Node(int _key,int _val,int _freq): key(_key), val(_val), freq(_freq) {}
};

// 我们定义两个哈希表，第一个 freq_table 以频率 freq 为索引，
// 每个索引存放一个双向链表，这个链表里存放所有使用频率为 freq 的缓存，
// 缓存里存放三个信息，分别为键 key，值 value，以及使用频率 freq。

// 第二个 key_table 以键值 key 为索引，每个索引存放对应缓存在 freq_table 中链表里的内存地址，
// 这样我们就能利用两个哈希表来使得两个操作的时间复杂度均为 O(1)。
// 同时需要记录一个当前缓存最少使用的频率 minFreq，这是为了删除操作服务的。

class LFUCache {
    int minfreq, capacity;
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int _capacity) : capacity(_capacity) {
        minfreq = 0;
        key_table.clear();
        freq_table.clear();
    } 

    int get(int key) {
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            return -1;
        }

        auto node = key_table[key]; 
        int freq = node->freq;
        int val = node->val;
        freq_table[freq].erase(node);
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (minfreq == freq) 
                minfreq += 1; 
        }

        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        auto iter = key_table.find(key);
        if (iter == key_table.end()) {
            // 缓存已满,需要删除操作
            if (key_table.size() == capacity) {
                auto it2 = freq_table[minfreq].back();
                key_table.erase(it2.key);
                freq_table[minfreq].pop_back();
                if (freq_table[minfreq].size() == 0) {
                    freq_table.erase(minfreq);
                }
            }

            freq_table[1].push_front(Node(key, value, 1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        } else {
            //与get一致, 但需要更新缓存
            list<Node>::iterator node = iter->second;
            int freq = node->freq;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) {
                freq_table.erase(freq);
                if (minfreq == freq) {
                    minfreq += 1;
                }
            }

            freq_table[freq + 1].push_front(Node(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};

#endif