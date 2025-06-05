#include <vector>
#include <stack>
using namespace std;
class AVLTree{

    private:

    struct TreeNode 
    {
    int val;
    int H;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), H(0) {}
};
    TreeNode* root = nullptr;

    int height(TreeNode *node)
    {
        return node==nullptr?-1:node->H;
    }
    
    void updateH(TreeNode *node)
    {
        node->H=max(height(node->left),height(node->right))+1;
    }

    int getBalance(TreeNode *node)
    {
        return node?height(node->left)-height(node->right):0;
    }

    TreeNode *rotate_left(TreeNode *node)
    {
        TreeNode *child = node->right;
        TreeNode *grandChild = child->left;
        child->left = node;
        node->right = grandChild;
        updateH(node);
        updateH(child);
        return child;
    }

    TreeNode *rotate_right(TreeNode *node)
    {
        TreeNode *child = node->left;
        TreeNode *grandChild = child->right;
        child->right = node;
        node->left = grandChild;
        updateH(node);
        updateH(child);
        return child;
    }

    TreeNode *Balance(TreeNode *node)
    {
        if (!node)return nullptr;
        int F=getBalance(node);
        if(F>1)
        {
            if(getBalance(node->left)>=0)
            {
                return rotate_right(node);
            }
            else
            {
                node->left=rotate_left(node->left);
                return rotate_right(node);
            }
        }
        if(F<-1)
        {
            if(getBalance(node->right)<=0)
            {
                return rotate_left(node);
            }
            else
            {
                node->right=rotate_right(node->right);
                return rotate_left(node);
            }
            return node;
        }
        return node;
    }
    
    void destroy(TreeNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}


    public:

    void insert(int val) {
    if (!root) {
        root = new TreeNode(val);
        return;
    }
    TreeNode* cur = root;
    TreeNode* parent = nullptr;
    stack<TreeNode*> path;

    while (cur) {
        path.push(cur);
        if (val == cur->val) return; 
        parent = cur;
        if (val < cur->val) cur = cur->left;
        else cur = cur->right;
    }

    TreeNode* newNode = new TreeNode(val);
    if (val < parent->val) parent->left = newNode;
    else parent->right = newNode;

    TreeNode* child = nullptr;
    while (!path.empty()) {
        TreeNode* node = path.top();
        path.pop();

        updateH(node);
        int balance = getBalance(node);

        if (balance > 1 && val < node->left->val)
            child = rotate_right(node);
    
        else if (balance < -1 && val > node->right->val)
            child = rotate_left(node);
        
        else if (balance > 1 && val > node->left->val) {
            node->left = rotate_left(node->left);
            child = rotate_right(node);
        }
        
        else if (balance < -1 && val < node->right->val) {
            node->right = rotate_right(node->right);
            child = rotate_left(node);
        } else {
            child = node;
        }

        if (!path.empty()) {
            TreeNode* p = path.top();
            if (p->left == node) p->left = child;
            else p->right = child;
        } else {
            root = child;
        }
    }
}

    void remove(int val) {
    TreeNode* cur = root;
    TreeNode* parent = nullptr;
    std::stack<TreeNode*> path;

    
    while (cur && cur->val != val) {
        path.push(cur);
        parent = cur;
        if (val < cur->val)
            cur = cur->left;
        else
            cur = cur->right;
    }
    if (!cur) return; 

    
    if (!cur->left || !cur->right) {
        TreeNode* child = cur->left ? cur->left : cur->right;
        if (!parent)
            root = child;
        else if (parent->left == cur)
            parent->left = child;
        else
            parent->right = child;
        delete cur;
    } else {
        TreeNode* succ = cur->right;
        TreeNode* succParent = cur;
        path.push(cur);
        while (succ->left) {
            path.push(succ);
            succParent = succ;
            succ = succ->left;
        }
        cur->val = succ->val;
        TreeNode* succChild = succ->right;
        if (succParent->left == succ)
            succParent->left = succChild;
        else
            succParent->right = succChild;
        delete succ;
    }
    TreeNode* child = nullptr;
    while (!path.empty()) {
        TreeNode* node = path.top(); path.pop();
        updateH(node);
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            child = rotate_right(node);
        
        else if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotate_left(node->left);
            child = rotate_right(node);
        }
        
        else if (balance < -1 && getBalance(node->right) <= 0)
            child = rotate_left(node);
        
        else if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotate_right(node->right);
            child = rotate_left(node);
        } else {
            child = node;
        }

        if (!path.empty()) {
            TreeNode* parent = path.top();
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        } else {
            root = child;
        }
    }
}
    vector<int> inorder() {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode* cur = root;

        while (cur || !stk.empty()) {
            while (cur) {
                stk.push(cur);
                cur = cur->left;
            }
            cur = stk.top(); stk.pop();
            result.push_back(cur->val);
            cur = cur->right;
        }
        return result;
    }
      AVLTree(vector<int> vec)
    {
    for (int val : vec) {
        insert(val);  
    }
    }
    ~AVLTree() {//析构函数
    destroy(root);
    }
};
