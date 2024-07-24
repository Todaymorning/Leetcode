// https://leetcode.cn/problems/binary-tree-level-order-traversal/
// 102.二叉树的层序遍历
// 给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
// 树中节点数目在范围 [0, 2000] 内
// -1000 <= Node.val <= 1000

#include<iostream>
#include<vector>
#include<queue>
using std::vector;
using std::queue;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 二叉树的层序遍历
// 递归法
// while for(stack queue)




// 递归法
class Solution_D1 {
    void order(TreeNode* cur, vector<vector<int>>& vec, int depth) {
        if(cur == nullptr) return;
        // 前序位置
        if(depth == int(vec.size())) vec.push_back(vector<int>());   // 添加新行
        vec[depth].push_back(cur->val);                         // 在新行添加元素
        order(cur->left, vec, depth+1);
        order(cur->right, vec, depth+1);
    }
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        int depth = 0;
        order(root, result, depth);
        return result;
    }
};

// 15:40——15：58
// 使用 quequ存储每一层的节点以供处理
// queue先进先出 先添左再添右
class Solution_D2 {
    void order(TreeNode* root, vector<vector<int>>& result) {
        if(root == nullptr) return;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        // while 循环控制从上向下一层层遍历
        while(!q.empty()) {
            depth++;    // 层数加一
            int size = q.size();
            result.push_back(vector<int>(size, 0));    // 每进入新的一层就新增加一行
            // for 循环控制每一层从左向右遍历
            for(int i=0; i<size; i++) {
                TreeNode* cur = q.front();
                q.pop();
                result[depth-1][i] = cur->val;  // depth - 1
                if(cur->left != nullptr) q.push(cur->left);
                if(cur->right != nullptr) q.push(cur->right);
            }
        }
    }
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        order(root, result);
        return result;
    }
};






// 2024年4月27日
// 16:48--16:56
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(root == nullptr) return result;
        queue<TreeNode*> q;
        q.push(root);
        int size = 1;
        int level = 0;
        TreeNode* temp;
        while(!q.empty()) {
            result.push_back(vector<int>(size));
            for(int i=0; i<size; i++) {
                temp = q.front();
                q.pop();
                result[level][i] = temp->val;
                if(temp->left != nullptr) q.push(temp->left);
                if(temp->right != nullptr) q.push(temp->right);
            }
            size = q.size();
            level++;
        }
        return result;
    }
};