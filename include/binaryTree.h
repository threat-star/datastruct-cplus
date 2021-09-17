#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include<iostream>
#include<vector>
#include<assert.h>
#include<stack>

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

    // TreeNode* deleteNode(TreeNode* root, int key) 
    // {
    //     if (root == nullptr)    return nullptr;
    //     if (key > root->val)    root->right = deleteNode(root->right, key);     // 去右子树删除
    //     else if (key < root->val)    root->left = deleteNode(root->left, key);  // 去左子树删除
    //     else    // 当前节点就是要删除的节点
    //     {
    //         if (! root->left)   return root->right; // 情况1，欲删除节点无左子
    //         if (! root->right)  return root->left;  // 情况2，欲删除节点无右子
    //         TreeNode* node = root->right;           // 情况3，欲删除节点左右子都有 
    //         while (node->left)          // 寻找欲删除节点右子树的最左节点
    //             node = node->left;
    //         node->left = root->left;    // 将欲删除节点的左子树成为其右子树的最左节点的左子树
    //         root = root->right;         // 欲删除节点的右子顶替其位置，节点被删除
    //     }
    //     return root;    
    // }

bool BinaryTree::removeNode( int val )
{
    //情况1： 如果删除的是叶子节点，直接删
    //情况2： 如果删除的节点只有一个子树，直接替上去
    //情况3:  如果有两个children，则用右孩子的最左叶子节点代替。
    if (m_root == nullptr) return false;
    
}

vector<int> BinaryTree::preOrder()
{
    //前序
    stack<treeNode*> stk;
    stk.push(m_root);
    while (!stk.empty()) {
        auto& top = stk.top();
        cout << top->m_val << " ";
        stk.pop();
        if (top->right) {
            stk.push(top->right);
        }

        if (top->left) {
            stk.push(top->left);
        }
    }
}

vector<int> BinaryTree::inOrder()
{
     //中序
    stack<treeNode*> stk;
    auto root = m_root;
    while (!stk.empty() || root != nullptr) {
       
        if (root != nullptr) {
            stk.push(root);  
            root = root->left;
        } else {
            root = stk.top();
            cout << root->m_val << " ";
            stk.pop();
            root = root->right;
        }
    }
}

vector<int> BinaryTree::afterOrder()
{
    //h代表最近一次弹出的节点，c代表栈顶节点
    if (m_root != nullptr) {
        stack<treeNode*> stk;
        stk.push(m_root);
        treeNode* h = m_root;

        while (!stk.empty()) {
            auto c = stk.top();

            //未打印过子节点, 先遍历
            if (c->left != nullptr && h != c->left && h != c->right) { 
                stk.push(c->left);
            } else if (c->right != nullptr && h != c->right) {   //未打印过右子树
                stk.push(c->right);
            } else {
                //auto top = stk.top();
                cout << c->m_val << " ";
                stk.pop();
                
                h = c;
            }
        }
    }

}

// //利用层次遍历重建满二叉树;
// treeNode* re_build_tree(vector<int> vec) {
//     int n = vec.size();
//     if (n == 0) {
        
//     }
// }


#endif



