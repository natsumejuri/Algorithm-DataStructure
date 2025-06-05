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
TreeNode *root==new TreeNode(0);

public:

BinarySearchTree(vector<int> arr)//构造函数，读取数组转换为二叉搜索树结构
{
    if(arr.empty())return;
    TreeNode *root=new TreeNode(arr[0]);
    if(arr.size()==1)return;
    for(int i=1;i<arr.size();i++){
        insert(arr[i]);
    }
}
vector<int> bfs()//广度遍历
{
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
    if(cur->left==nullptr||cur->right==nullptr)
    {
        TreeNode *child=cur->left!=nullptr?cur->left:cur->right;
        if(cur!=root)
        {
            if(pre->left==cur)pre->left=child;
            else pre->right=child;
        }
        else root=child;
        delete cur;
    }
    else
    {
        TreeNode *tmp=cur->right;
        while(tmp->left!=nullptr)
        {
            tmp=tmp->left;
        }
        int val=tmp->val;
        remove(tmp->val);
        cur->val=val;
    }
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
