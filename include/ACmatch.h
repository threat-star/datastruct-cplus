#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>

using namespace std;

//和字符串匹配一样，next数组 变为 failure pointer

class AcNode
{
public:
	AcNode() {};
	AcNode(char data) :isEndingChar(false), m_data(data), length(-1)
	{
	};
	char m_data;
	AcNode* children[26];
	bool isEndingChar; //结尾字符
	int length; //当isEndingChar = true，记录模式串的长度
	AcNode* fail;
	
};

class Ac
{
public:
	Ac() {}
	Ac(vector<string> vec);
	void insert(string str);
	void remove(string str);
	bool search(string str);
	void buildFailurePointer();
	void match(string str);
private:
	AcNode* root;
};

Ac::Ac(vector<string> vec) {
	memset(root, 0, sizeof(AcNode) * 26);

	for (auto i : vec)
	{
		insert(i);
	}
}

void Ac::insert(string str)
{
	AcNode *cur= root;
	for (int i=0;i<str.size();++i)
	{
		if (str[i]<'a' || str[i]>'z')
		{
			cerr << "cin error" << endl;
		}

		int index=str[i] - 'a';
		if (cur->children[i] == nullptr)
		{
			cur->children[i] = new AcNode(str[i]);
		}

		cur = cur->children[index];
	}

	cur->isEndingChar = true;
	cur->length = str.size();
	return;
}

void Ac::remove(string str)
{
	AcNode* cur = root;
	for (int i=0;i<str.size();++i)
	{
		if (str[i] < 'a' || str[i]>'z')
		{
			cerr << "cin error" << endl;
		}

		int index = str[i] - 'a';
		if (cur->children[i] == nullptr)
		{
			cerr << " remove nullptr error" << endl;
			return;
		}

		cur = cur->children[index];
	}

	cur->isEndingChar = false;
	return;
}

bool Ac::search(string str)
{
	AcNode* cur = root;
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] < 'a' || str[i]>'z')
		{
			cerr << "search error" << endl;
			return false;
		}

		int index = str[i] - 'a';
		if (cur->children[i] == nullptr)
		{
			return false; 
		}

		cur = cur->children[index];
	}

	return cur->isEndingChar;
}

void Ac::buildFailurePointer()
{
	queue<AcNode*> que;
	que.push(root);

	while (!que.empty())
	{
		AcNode* p = que.front();
		que.pop();
		AcNode* pc;
		for (int i = 0; i < 26; ++i)
		{
			pc=p->children[i]; //循环遍历子孩子；
			if (pc == NULL) continue;
			if (p == root)
			{
				pc->fail = root;
			}
			else
			{
				AcNode* q = p->fail;
				while (q != NULL)
				{
					AcNode* qc = q->children[pc->m_data - 'a'];
					if (qc != NULL)
					{
						pc->fail = qc;
						break;
					}
					q = q->fail;
				}

				if (q == NULL)
				{
					pc->fail = root;
				}
			}

			que.push(pc);
		}
	}
}

void Ac::match(string str)
{
	int n = str.length();
	AcNode* p = root;
	for (int i=0;i<n;++i)   //时间复杂度为，O(length * n)  ,length为敏感词的长度;
	{
		int idx = str[i] - 'a';
		while (p->children[idx] == NULL && p!=root) //没有匹配到，就找失败指针
		{
			p = p->fail;
		}

		p = p->children[idx];
		if (p == NULL) p = root; //没有匹配的，从root开始重新
		AcNode* tmp = p;
		while (tmp!=root) //多模式匹配，找到全部能匹配上的。  
		{
			if (tmp->isEndingChar == true)
			{
				int pos = i - tmp->length + 1;
				cout << "匹配起始下标 " << pos << "；长度 " << tmp->length;
			}
			tmp = tmp->fail; 
		}

	}
}

