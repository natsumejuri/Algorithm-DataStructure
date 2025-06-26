#include <vector>
#include <queue>
using namespace std;
class BinarySearchTree{

private:

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};
TreeNode *root=nullptr;
public:

BinarySearchTree(){}
BinarySearchTree(vector<int> arr)//构造函数，读取数组转换为二叉搜索树结构
{
    for(int i:arr){
        insert(i);
    }
}
vector<int> bfs()//广度遍历
{
    if (root == nullptr) return {};
    TreeNode *cur=root;
    queue<TreeNode *> queue;
    queue.push(root);
    vector<int> vec;
    while (!queue.empty()) 
    {
        TreeNode *node = queue.front();
        queue.pop();              
        vec.push_back(node->val); 
        if (node->left != nullptr)queue.push(node->left); 
        if (node->right != nullptr)queue.push(node->right); 
    }
    return vec;
}

TreeNode* search(int num)//搜索节点
{
    TreeNode *cur=root;
    while(cur!=nullptr){
        if(cur->val<num)cur=cur->right;
        else if(cur->val>num)cur=cur->left;
        else break;
    }
    return cur;
}
void insert(int num)//插入节点
{
    if (root == nullptr) 
    {
    root = new TreeNode(num);
    return;
    }

    TreeNode *cur=root,*pre=nullptr;
    while(cur!=nullptr){
        if(cur->val==num)return;
        pre=cur;
        if(cur->val<num)cur=cur->right;
        else cur=cur->left;
            
}
        TreeNode *node=new TreeNode(num);
        if (pre->val<num)pre->right=node;
        if (pre->val>num)pre->left=node;
}
void remove(int num)//删除节点
{
    TreeNode *cur=root,*pre=nullptr;
    while(cur!=nullptr){
        if(cur->val==num)break;
        pre=cur;
        if(cur->val<num)cur=cur->right;
        else cur=cur->left;
    }
    if(cur==nullptr)return;
    if (cur->left && cur->right) {
        TreeNode *succ=cur->right;
        TreeNode *succPre=cur;
        while (succ->left) {
            succPre=succ;
            succ=succ->left;
        }
        cur->val=succ->val;
        cur=succ;
        pre=succPre;
    }
    TreeNode *child=(cur->left)?cur->left:cur->right;

    if (!pre) {
        root=child;
    } else if (pre->left==cur) {
        pre->left=child;
    } else {
        pre->right=child;
    }
    delete cur;
}

~BinarySearchTree() {//析构函数
    destroy(root);
}
void destroy(TreeNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}
};
