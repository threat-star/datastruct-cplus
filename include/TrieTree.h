#pragma once

#include<iostream>
#include<vector>
#include<string.h>


using namespace std;
struct TrieNode {
	char data;
	bool isEndChar;
	TrieNode* arr[26];
	TrieNode(char tmpData) :data(tmpData),isEndChar(false) {
		memset(arr, 0, sizeof(TrieNode*) * 26);
	}
	~TrieNode()
	{
		for (int i = 0; i < 26; ++i) 
		{ 
			if (arr[i]!=nullptr)
			{
				delete arr[i];
				arr[i] = nullptr;
			}
		}
	}
};

class TrieTree {
public:
	TrieTree();
	TrieTree(std::vector<std::string> vec);
	~TrieTree() {
		delete root;
		root = nullptr;
	}
	void insert(std::string word);
	bool search(std::string word);
	void remove(std::string word);
private:
	TrieNode* root;
};

TrieTree::TrieTree() {
	root = new TrieNode('/');
}

TrieTree::TrieTree(std::vector<std::string> vec) {
	root = new TrieNode('/');
	for (auto word:vec) {
		
		insert(word);
	}
}

void TrieTree::insert(std::string word) {
	if (word.size() == 0) 
		return;
	TrieNode* curNode = root;
	//"A" - "Z" (65-90)
	//"a" - "z" (97-122)
	for (int i = 0; i < word.size();i++) {

		if (word[i]<'a'||word[i]>'z') {
			cerr << "插入错误"<<endl;
		}
		int idx=word[i] - 'a';
		if (curNode->arr[idx]==nullptr) {
			curNode->arr[idx] = new TrieNode(word[i]);
		}
		curNode = curNode->arr[idx];
	}
	curNode->isEndChar = true;
	cout << word << endl;
	return;
}


bool TrieTree::search(std::string word) {
	if (word.size() == 0)
		return false;
	TrieNode* curNode = root;
	for (int i = 0; i < word.size(); ++i) {
		int idx = word[i] - 'a';
		if (curNode->arr[idx] == nullptr) {
			return false;
		}
		curNode = curNode->arr[idx];
	}
	return curNode->isEndChar;
}

void TrieTree::remove(std::string word) {
	if (word.size() == 0)
		return;
	TrieNode* curNode = root;
	for (int i = 0; i < word.size(); ++i) {
		int idx = word[i] - 'a';
		if (curNode->arr[idx] == nullptr) {
			cerr << "Trie have not word" << endl;
			return;
		}
		curNode = curNode->arr[idx];
	}
	curNode->isEndChar = false;
	return;
}

//  test example
//vector<string> vec = { "word","wo","we","am","excepetion" };
//TrieTree Trie(vec);
//cout << Trie.search("word");
//cout << Trie.search("dump") << endl;
//Trie.insert("dump");
//cout << Trie.search("dump") << endl;
//Trie.remove("dump");
//cout << Trie.search("dump") << endl;