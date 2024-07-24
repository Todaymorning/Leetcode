// Easy
// 513. 找树左下角的值
// 给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。
// 假设二叉树中至少有一个节点。

// 提示:
// 二叉树的节点个数的范围是 [1,104]
// -231 <= Node.val <= 231 - 1 

#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using std::stack;
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
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        return 1;
    }
};


// 二叉树层序遍历方法：
// 递归法
// queue迭代层序遍历


// queue迭代层序遍历
// while for 层序遍历
class Solution_M1 {
    int traverse(TreeNode* root) {
        if(root == nullptr) return -1;  // 可以不用判断
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* cur;
        int result;
        while(!q.empty()) {
            int size = q.size();
            vector<int> results(size, 0);
            for(int i=0; i<size; i++) {
                cur = q.front();
                q.pop();
                results[i] = cur->val;
                if(cur->left != nullptr) q.push(cur->left);
                if(cur->right != nullptr) q.push(cur->right);
            }
            result = results[0];
        }
        return result;
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        return traverse(root);
    }
};

// 迭代层序遍历
// 深度回溯
class Solution_M2 {
    int depth = -1;
    void traverse(TreeNode* root, vector<vector<int>>& results) {
        if(root == nullptr) return;
        // 前序位置
        depth++;
        if(depth == int(results.size())) results.push_back(vector<int>());
        results[depth].push_back(root->val);
        traverse(root->left, results);
        traverse(root->right, results);
        depth--;
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        vector<vector<int>> results;
        traverse(root, results);
        return results.back()[0];
    }
};

// 递归层序遍历，隐藏深度回溯
class Solution_M3 {
    void traverse(TreeNode* root, vector<vector<int>>& results, int depth) {
        if(root == nullptr) return;
        // 前序位置
        if(depth == int(results.size())) results.push_back(vector<int>());
        results[depth].push_back(root->val);
        traverse(root->left, results, depth+1);
        traverse(root->right, results, depth+1);
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        vector<vector<int>> results;
        traverse(root, results, 0);
        return results.back()[0];
    }
};


// 22:17——22：27
// 递归前序遍历，找到深度最大的子叶节点
// 深度回溯 depth result
class Solution_D1 {
    int result;
    int maxDepth = INT_MIN;
    int depth = 0;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        // 前序遍历，中左右，因为先遍历左侧，因此哪怕左右深度一样，只有左子叶会执行if中的内容
        // 右边由于 maxDepth 已经更新，条件不成立，因此不会执行
        if(depth > maxDepth) {
            maxDepth = depth;
            if(root->left == nullptr && root->right == nullptr) {
                result = root->val;
            }
        }
        depth++;
        traverse(root->left);
        traverse(root->right);
        depth--;
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        traverse(root);
        return result;
    }
};

// 递归后序遍历，找到深度最大的子叶节点
// 深度回溯 depth result
class Solution_D1 {
    int result;
    int maxDepth = INT_MIN;
    int depth = 0;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        depth++;
        traverse(root->left);
        traverse(root->right);
        depth--;
        // 后序遍历，左右中，因为先遍历左侧，因此哪怕左右深度一样，只有左子叶会执行if中的内容
        // 右边由于 maxDepth 已经更新，条件不成立，因此不会执行
        if(depth > maxDepth) {
            maxDepth = depth;
            if(root->left == nullptr && root->right == nullptr) {
                result = root->val;
            }
        }
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        traverse(root);
        return result;
    }
};