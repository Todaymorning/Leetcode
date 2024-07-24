// 226. 翻转二叉树
// 每个节点的左右子节点交换

#include<iostream>
#include<stack>
using std::stack;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};



// 前序位置的代码在刚刚进入一个二叉树节点的时候执行；
// 后序位置的代码在将要离开一个二叉树节点的时候执行；
// 中序位置的代码在一个二叉树节点左子树都遍历完，即将开始遍历右子树的时候执行。


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 递归
// 用遍历的思维
// 递归遍历，对每个节点都交换其左右子节点
// 前中后序位置都可以，但中序位置需要略作修改

class Solution_D1_pre {
    // 二叉树遍历
    void traverse(TreeNode* cur) {
        if(cur == nullptr) return;
        // 前序位置
        // 每一个节点需要做的事就是交换它的左右子节点
        TreeNode* temp = cur->left;
        cur->left = cur->right;
        cur->right = temp;
        
        traverse(cur->left);
        traverse(cur->right);
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        traverse(root);
        return root;    // 返回
    }
};

class Solution_D1_in {
    // 二叉树遍历
    void traverse(TreeNode* cur) {
        if(cur == nullptr) return;
        traverse(cur->left);    // 左边遍历完了，右边还没遍历，因此交换后还是遍历左边
        // 中序位置
        // 每一个节点需要做的事就是交换它的左右子节点
        TreeNode* temp = cur->left;
        cur->left = cur->right;
        cur->right = temp;
        traverse(cur->left);
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        traverse(root);
        return root;
    }
};

class Solution_D1_post {
    // 二叉树遍历
    void traverse(TreeNode* cur) {
        if(cur == nullptr) return;
        traverse(cur->left);
        traverse(cur->right);
        // 后序位置
        // 每一个节点需要做的事就是交换它的左右子节点
        TreeNode* temp = cur->left;
        cur->left = cur->right;
        cur->right = temp;
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        traverse(root);
        return root;
    }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 递归
// 用分解问题的思维
// 对自己应该做什么，就对子树做什么
class Solution_L2 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return root;
        TreeNode* left = invertTree(root->left);    // 左子树翻转
        TreeNode* right = invertTree(root->right);  // 右子树翻转
        root->left = right;                         // 左右子树交换
        root->right = left;
        return root;
    }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 迭代
// 比较统一的迭代方式
// 11:23——11:33
// 前序 中、左、右，栈内应该是右、左、中
class Solution_D2_pre {
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        stack<TreeNode*> stk;
        stk.push(root);
        while(!stk.empty()) {
            TreeNode* cur = stk.top();
            if(cur != nullptr) {
                stk.pop();
                if(cur->right != nullptr) stk.push(cur->right); // 右
                if(cur->left != nullptr) stk.push(cur->left);   // 左
                stk.push(cur);                                  // 中
                stk.push(nullptr);
            }
            else {
                stk.pop();
                cur = stk.top();
                stk.pop();
                TreeNode* temp = cur->left;
                cur->left = cur->right;
                cur->right = temp;
            }
        }
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        traverse(root);
        return root;
    }
};

// 中序 左、中、右，栈内应该是右、中、左
class Solution_D2_in {
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        stack<TreeNode*> stk;
        stk.push(root);
        while(!stk.empty()) {
            TreeNode* cur = stk.top();
            if(cur != nullptr) {
                stk.pop();
                if(cur->right != nullptr) stk.push(cur->right); // 右
                stk.push(cur);                                  // 中
                stk.push(nullptr);
                if(cur->left != nullptr) stk.push(cur->left);   // 左
            }
            else {
                stk.pop();
                cur = stk.top();
                stk.pop();
                TreeNode* temp = cur->left;
                cur->left = cur->right;
                cur->right = temp;
            }
        }
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        traverse(root);
        return root;
    }
};

// 后序 左、右、中，栈内应该是中、右、左
class Solution_D2_post {
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        stack<TreeNode*> stk;
        stk.push(root);
        while(!stk.empty()) {
            TreeNode* cur = stk.top();
            if(cur != nullptr) {
                stk.pop();
                stk.push(cur);                                  // 中
                stk.push(nullptr);
                if(cur->right != nullptr) stk.push(cur->right); // 右
                if(cur->left != nullptr) stk.push(cur->left);   // 左
            }
            else {
                stk.pop();
                cur = stk.top();
                stk.pop();
                TreeNode* temp = cur->left;
                cur->left = cur->right;
                cur->right = temp;
            }
        }
    }
public:
    TreeNode* invertTree(TreeNode* root) {
        traverse(root);
        return root;
    }
};




