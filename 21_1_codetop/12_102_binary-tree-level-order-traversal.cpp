// https://leetcode.cn/problems/binary-tree-level-order-traversal

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