// 199. 二叉树的右视图
// 给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

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
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


// 17:00-17:15-17:25-17:31
// 只迭代右子树错误，改为正确方法，忘记添加root->val取排除错误
// 递归法：层序遍历后取每一行的最后一列
class Solution_D1 {
    void view(TreeNode* root, vector<vector<int>>& result, int depth) {
        if(root == nullptr) return;
        if(int(result.size()) == depth) result.push_back(vector<int>());
        result[depth].push_back(root->val);  // !!!!!!!!!!!!!!!!!!
        view(root->left, result, depth + 1);
        view(root->right, result, depth + 1);
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<vector<int>> order;
        view(root, order, 0);               // 层级遍历
        int size = order.size();
        vector<int> result(size, 0);
        for(int i=0; i<size; i++) {
            result[i] = order[i].back();    // 获取每一行的最后一列，就是右视图
        }
        return result;
    }
};



// 迭代法
// 9:44——9:53

class Solution_D2 {
    void view(TreeNode* root, vector<int>& result) {
        if(root == nullptr) return;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            TreeNode* cur;
            int size = q.size();
            vector<int> temp(size, 0);
            for(int i=0; i<size; i++) {
                cur = q.front();
                q.pop();
                temp[i] = cur->val;
                if(cur->left != nullptr) q.push(cur->left);
                if(cur->right != nullptr) q.push(cur->right);
            }
            result.push_back(temp.back());  // 每一层的最右侧
        }
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        view(root, result);
        return result;
    }
};