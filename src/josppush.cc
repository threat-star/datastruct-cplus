#include<iostream>
#include<vector>

struct listNode
{
    int m_val;
    listNode* next;
    listNode( int val ) : m_val( val ), next( nullptr )
    {

    }
};

listNode* creatListAndReturnStart( int count, int start )
{
    if( count <= 0 )
    {   
        return nullptr;
    }

    listNode* head = new listNode( 0 );
    listNode* cur = head, *startList;
    int i = 1;
    while( i < count )
    {
        listNode* tmp = new listNode( i );
        cur->next = tmp;
        cur = cur->next;
        if( i == start )
        {
            startList = cur;
        }
        ++i;
    }

    cur->next = head;
    return startList;
}

void josePhusList( listNode* head, int k, int count)
{
    if( head == nullptr || head->next == head || k < 1 )
    {
        return;
    }

    listNode* last = head;
    while( last->next != head )
    {   
        last = last->next;
    }

    int curCount = 0, outNum = 0;
    while( head != last )
    {
        if( ++curCount == k )
        {
            if( outNum == count )
            {
                std::cout << last->m_val;
                return;
            }
            std::cout << last->m_val << "->";
            last->next = head->next;
            curCount = 0;
            outNum++;
        }
        else
        {
            last = last->next;
        }
        head = last->next;
    }
}


int main()
{
    int count, start, k;
    std::cin >> count >> start >> k;
    listNode* head = creatListAndReturnStart( count, start );
    listNode* cur = head;
    josePhusList( head, k, count );

    return 0;
}