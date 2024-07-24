// 二叉树的中序遍历
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
    TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


// 递归法中序遍历
class Solution_D1 {
    void traversal(TreeNode* cur, vector<int>& ver) {
        if(cur == nullptr) return;
        // 前序位置
        traversal(cur->left, ver);      // 左
        // 中序位置
        ver.push_back(cur->val);        // 中
        traversal(cur->right, ver);     // 右
        // 后序位置
    }
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> result;
        traversal(root, result);
        return result;
    }
};


// 栈迭代法中序遍历
class Solution_D2 {
    void traversal(TreeNode* cur, vector<int>& vec) {
        if(cur == nullptr) return;
        stack<TreeNode*> stk;
        while(cur != nullptr || !stk.empty()) {
            // 一直往左，直到左边为空才开始弹出一个
            if(cur != nullptr) {
                stk.push(cur);
                cur = cur->left;            // 左
            }
            else {
                cur = stk.top();
                stk.pop();
                vec.push_back(cur->val);    // 中
                cur = cur->right;           // 右，不要判断是否为空，否则上面又会添加已经处理过的左节点，死循环了
            }
        }

    }
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> result;
        traversal(root, result);
        return result;
    }
};


// 中序遍历，比较统一的迭代法
// 用 nullptr做标记
// 中序遍历的顺序是 左、中、右，因此在栈内的顺序应该是右、中、左

class Solution_D3 {
    void traversal(TreeNode* cur, vector<int>& vec) {
        if(cur == nullptr) return;
        stack<TreeNode*> stk;
        stk.push(cur);
        while(!stk.empty()) {
            TreeNode* cur = stk.top();  // 当前节点
            if(cur != nullptr) {
                // 不是需要处理的节点
                stk.pop();  // 弹出，避免重复处理，因为后面还要重新压入站内
                if(cur->right != nullptr) stk.push(cur->right); // 右
                stk.push(cur);                                  // 中
                stk.push(nullptr);
                if(cur->left != nullptr) stk.push(cur->left);   // 左
            }
            else {
                stk.pop();  // 弹出需要处理的节点前的nullptr
                cur = stk.top();
                vec.push_back(cur->val);
                stk.pop();  // 处理完后弹出该节点
            }
        }
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};