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
    while(odd)
    {
        tmp->next=odd;
        odd=odd->next;
    }
    while(even)
    {
        tmp->next=even;
        even=even->next;
    }
    
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
    delete head;
    head=nullptr;
    Delete(head->next);
}