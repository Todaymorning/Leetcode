// 145.二叉树的后向遍历


#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using std::vector;
using std::stack;
using std::reverse;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


// 递归法
class Solution_D1 {
    void traversal(TreeNode* cur, vector<int>& vec) {
        if(cur == nullptr) return;
        traversal(cur->left, vec);      // 左
        traversal(cur->right, vec);     // 右
        // 后序位置，离开一个节点的时候 
        vec.push_back(cur->val);        // 中

    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};

// 迭代法
class Solution_D2 {
    void traversal(TreeNode* cur, vector<int>& vec) {
        if(cur == nullptr) return;
        stack<TreeNode*> stk;
        stk.push(cur);
        while(!stk.empty()) {
            TreeNode* temp = stk.top();
            stk.pop();
            vec.push_back(temp->val);
            if(temp->left != nullptr) stk.push(temp->left);     // 调整顺序
            if(temp->right != nullptr) stk.push(temp->right);
        }
        reverse(vec.begin(), vec.end());    // 将结果翻转
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};



// 后序遍历，比较统一的迭代法
// 用 nullptr做标记
// 后序遍历的顺序是左、右、中， 因此压入栈内的顺序是 中、右、左
class Solution_D3 {
    void traversal(TreeNode* cur, vector<int>& vec) {
        if(cur == nullptr) return;
        stack<TreeNode*> stk;
        stk.push(cur);
        while(!stk.empty()) {
            TreeNode* cur = stk.top();
            if(cur != nullptr) {
                stk.pop();  // 弹出，避免重复处理
                stk.push(cur);                                  // 中
                stk.push(nullptr);
                if(cur->right != nullptr) stk.push(cur->right); // 右
                if(cur->left != nullptr) stk.push(cur->left);   // 左
            }
            else {
                stk.pop();  // 弹出nullptr
                cur = stk.top();
                stk.pop();
                vec.push_back(cur->val);
            }
        }
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};


class Solution_D3_2 {
    void traversal(TreeNode* root, vector<int>& result) {
        if(root == nullptr) return;
        stack<TreeNode*> stk;
        stk.push(root);
        while(!stk.empty()) {
            TreeNode* cur = stk.top();
            if(cur != nullptr) {
                stk.pop();  //
                stk.push(cur);
                stk.push(nullptr);
                if(cur->right != nullptr) stk.push(cur->right);
                if(cur->left != nullptr) stk.push(cur->left);
            }
            else {
                stk.pop();  //
                cur = stk.top();
                stk.pop();
                result.push_back(cur->val);
            }
        }
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};




