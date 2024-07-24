// 144.二叉树的前向遍历
// 给你二叉树的根节点 root，返回它节点值的前序遍历。

#include<iostream>
#include<vector>
#include<stack>
using std::vector;
using std::stack;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};




// 递归法
class Solution_D1 {
    // 
    void traversal(TreeNode* cur, vector<int>& vec) {
        if(cur == nullptr) return;
        vec.push_back(cur->val);    // 中
        traversal(cur->left, vec);  // 左
        traversal(cur->right, vec); // 右
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};


// 迭代法
class Solution_D2 {
    void traversal(TreeNode* cur, vector<int>& vec) {
        if(cur == nullptr) return;
        stack<TreeNode *> stk;
        stk.push(cur);
        while(!stk.empty()) {   // 用栈替代递归，但需要调整顺序
            TreeNode* temp = stk.top();
            stk.pop();
            vec.push_back(temp->val);                           // 中
            if(temp->right != nullptr) stk.push(temp->right);   // 右
            if(temp->left != nullptr) stk.push(temp->left);     // 左
        }


    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};


// 比较统一的迭代法
// 为将要处理的节点打上标记，在其后面再压入一个nullptr，以区分是否需要处理
// 前序遍历的顺序是 中、左、右，因此压入站内的顺序是右、左、中，在前序遍历位置 中 处理
class Solution_D3 {
    void traversal(TreeNode* cur, vector<int>& vec) {
        if(cur == nullptr) return;
        stack<TreeNode*> stk;
        stk.push(cur);
        while(!stk.empty()) {
            TreeNode* cur = stk.top();
            if(cur != nullptr) {
                stk.pop();      // 弹出,因为后面右中左三个节点都会重新压入，弹出避免重复处理
                if(cur->right != nullptr) stk.push(cur->right); // 右
                if(cur->left != nullptr) stk.push(cur->left);   // 左
                stk.push(cur);                                  // 中
                stk.push(nullptr);
            }
            else {  // 当前是nullptr,前一个需要处理
                stk.pop();  // 弹出需要处理的节点前加的nullptr
                cur = stk.top();
                vec.push_back(cur->val);
                stk.pop();    // 处理完后弹出
            }
        }
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};
