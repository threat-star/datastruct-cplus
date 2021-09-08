#include<iostream>

using namespace std;

// 1 -> 100 -> 2 -> 99 ->3 ->98
//变为 顺序的

struct listNode{
    int mval;
    listNode* next;
    listNode(int val)
    {
        mval=val;
        next=nullptr;
    }
};

listNode* CreateList(int* arr,int len)
{
    if(arr==nullptr || len<=0) return nullptr;
    listNode* head = new listNode(arr[0]),*pre=head;
    for(int i=1;i<len;++i)
    {
        listNode* tmp = new listNode(arr[i]);
        head->next=tmp;
        head=head->next;
    }
    return pre;
}

listNode* reverse(listNode* head)
{
    if(!head || !head->next) return head;
    listNode* pre=nullptr,*next;

    while(head)
    {
        next=head->next;
        head->next=pre;
        pre=head;
        head=next;
    }
    return pre;
}

listNode* listMerge(listNode* odd,listNode*even)
{
    if(!odd) return even;
    if(!even) return odd;
    listNode* head(0), *tmp=head;

    while(even && odd)
    {
        if(even->mval>odd->mval)
        {
            tmp->next=odd;
            odd=odd->next;
        }
        else
        {
            tmp->next=even;
            even=even->next;
        }
    }
    tmp->next = odd == nullptr ?  even : odd;
    
    return head->next;
}

listNode* recode(listNode* head)
{
    //1.奇偶拆分
    if(!head || !head->next){ return head;}
    listNode* odd=head,*tmpodd=odd;
    listNode* even=head->next,*tmpeven=even;
    while(even && even->next)
    {
        odd->next=even->next;
        odd=odd->next;
        even->next=odd->next;
        even=even->next;
    }
    //*************
    odd->next=nullptr;
    //*************
    tmpeven=reverse(tmpeven);
    head = listMerge(tmpodd,tmpeven);
    return head;
}

void listPrint(listNode* head)
{
    while(head)
    {
        cout<<head->mval<<" ";
        head=head->next;
    }
    cout<<endl;
}

void Delete(listNode* head)
{
    Delete(head->next);
    delete head;
    head=nullptr;
}


class Solution {
public:
    pair<listNode*, listNode*> my_reverse(listNode* head, listNode* tail) {
        listNode* prev = tail->next;
        listNode* p = head;
        while (prev != tail) {
            listNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }

    listNode* reverseKGroup(listNode* head, int k) {
        listNode* hair = new listNode(0);
        hair->next = head;
        listNode* pre = hair;
        while (head) {
            listNode* tail = pre; 
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (tail == nullptr) 
                    return hair->next;
            } 

            listNode* next = tail->next;
            pair<listNode*, listNode*> pairs = my_reverse(head, tail);
            pre->next = pairs.first;
            
            pre = pairs.second;
            head = next;
        }
        

        return hair->next;
    }
};
