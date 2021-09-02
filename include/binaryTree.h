#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

class treeNode
{
public:
    int m_val;    
    treeNode *left;
    treeNode *right;
    treeNode( int val = 0 ) : m_val( val ), left( nullptr ), right( nullptr )
    {

    }
};

class BinaryTree
{
private:
    treeNode* m_root;
    treeNode* getNext( treeNode* root );
    //treeNode* findSlot( int val );
public:
    BinaryTree( treeNode* root = nullptr ) : m_root( root )
    {

    }

    BinaryTree( const vector<int> vec );

    void addNode( int val );
    bool removeNode( int val );
    vector<int> preOrder();
    vector<int> inOrder();
    vector<int> afterOrder();
};

// treeNode* BinaryTree::findSlot( int val )
// {
//     treeNode *tmp = m_root; 
//     while( 1 )
//     {
//         if( tmp == nullptr )
//         {
//             return tmp;
//         }

//         if( val > tmp -> m_val )
//         {
//             tmp = tmp -> right;
//         }
//         else
//         {
//             tmp = tmp -> left;
//         }
//     }
// }

BinaryTree::BinaryTree( const vector<int> vec )
{
    int n = vec.size();
    if( n == 0 )
    {
        return;
    }

    m_root == new treeNode( vec[0] );
    for( int i = 0; i < n; ++i )
    {
        addNode( vec[i] );
    }
}

void BinaryTree::addNode( int val )
{
    if( m_root == nullptr )
    {
        m_root = new  treeNode( val );
        return;
    }

    treeNode *tmp = m_root;
    while( tmp )
    {
        if( val > tmp->m_val )
        {
            if( tmp->right == nullptr )
            {
                treeNode* cur = new treeNode( val );
                tmp -> right = cur;
                break;
            }
            
            tmp = tmp->right;
        }
        else if( val < tmp->m_val )
        {
            if( tmp->left == nullptr )
            {
                treeNode* cur = new treeNode( val );
                tmp -> left = cur;
            }

            tmp = tmp->left;
        }
        else
        {
            cerr << "val existing!";
            break;
        }
    }

}

treeNode* getNext( treeNode* root )
{
    while( root->left )
    {
        root = root->left;
    }

    return root;
}

bool BinaryTree::removeNode( int val )
{
    //情况1： 如果删除的是叶子节点，直接删
    //情况2： 如果删除的节点只有一个子树，直接替上去
    //情况3:  如果有两个children，则用右孩子的最左叶子节点代替。
    assert( m_root );
    treeNode* cur = m_root;
    treeNode* parent = nullptr;
    treeNode* delNode = cur;
    
    while( cur != nullptr && cur->m_val != val )
    {
        if( cur->m_val > val )
        {
            parent = cur;
            cur = cur->left;
        }
        else
        {
            parent = cur;
            cur = cur->right;
        }
    }

    if( cur == nullptr )
    {
        return false;
    }

    delNode = cur;
    if( !cur->left )  //只有右孩子
    {
        if( cur == m_root )
        {
            m_root = m_root->right; 
        }
        else if( cur == parent->left )
        {
            parent->left = cur->right;
        }
        else
        {
            parent->right = cur->right;
        }
    }   
    else if( !cur->right )  //只有左孩子
    {
       if( cur == m_root )
        {
            m_root = m_root->left; 
        }
        else if( cur == parent->left )
        {
            parent->left = cur->left;
        }
        else
        {
            parent->right = cur->left;
        }
    }
    else  //有两个children
    {
        treeNode* next = cur->right;
        parent = cur;
        while( next->left )
        {
            parent = next;
            next = next->left;
        }
        cur->m_val = next->m_val;
        delNode = next;
        parent->left = next->right; //维护它的右节点。
    }
    
    delete delNode;
    delNode = nullptr;
    return true;
}

vector<int> BinaryTree::preOrder()
{

}

vector<int> BinaryTree::inOrder()
{

}

vector<int> BinaryTree::afterOrder()
{


}


#endif



