// Easy
// 111. 二叉树的最小深度
// 给定一个二叉树，找出其最小深度。
// 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
// 说明: 叶子节点是指没有子节点的节点

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



// 9:50——9:58——10:25
// 递归分解问题
class Solution_M1 {
    int traverse(TreeNode* root) {
        if(root == nullptr) return 0;
        if(root->left == nullptr && root->right == nullptr) return 1;
        int min;
        if(root->left == nullptr || root->right == nullptr) {
            if(root->left != nullptr) min = traverse(root->left);
            else min = traverse(root->right);
        }
        else {
            int leftmin = traverse(root->left);
            int rightmin = traverse(root->right);
            min = leftmin < rightmin ? leftmin : rightmin;
        }
        return 1 + min;
    }
public:
    int minDepth(TreeNode* root) {
        int result = 0;
        result = traverse(root);
        return result;
    }
};

// 下面这种方法是错误的，结果和题目要求不符
class Solution_M1_2 {
    int traverse(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftmin = traverse(root->left);
        int rightmin = traverse(root->right);
        return 1 + (leftmin < rightmin ? leftmin : rightmin);
    }
public:
    int minDepth(TreeNode* root) {
        int result = 0;
        result = traverse(root);
        return result;
    }
};


// 递归分解问题
// 后序遍历
class Solution_D1 {
    int traverse(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftmin = traverse(root->left);
        int rightmin = traverse(root->right);
        if(root->left == nullptr && root->right != nullptr) {
            return 1 + leftmin;
        }
        if(root->left != nullptr && root->right == nullptr) {
            return 1 + rightmin;
        }
        return 1 + leftmin < rightmin ? leftmin : rightmin;

    }
public:
    int minDepth(TreeNode* root) {
        return traverse(root);
    }
};


// 11:10——11:15——11:24
// 递归 深度回溯
// 前序遍历
class Solution_M2 {
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        depth++;
        // 只有在遇到叶子节点的时候才更新深度
        if(root->left == nullptr && root->right == nullptr) {
            result = depth < result ? depth : result;
            // return;  // 这里不应该有return,会导致后面的 depth-- 没执行
        }
        traverse(root->left);
        traverse(root->right);
        depth--;
    }
public:
    int result = INT_MAX;   // 最大值，方便变小
    int depth = 0;
    int minDepth(TreeNode* root) {
        traverse(root);
        if(result==INT_MAX) return 0;   // 判断result是否更新过
        return result;
    }
};


// 11:28——
// 迭代遍历
// 队列层序遍历
class Solution {
    int traverse(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* cur;
        int level = 0;
        while(!q.empty()) {
            level++;
            int size = q.size();
            for(int i=0; i<size; i++) {
                cur = q.front();
                q.pop();
                // 因为是层序遍历，因此深度是逐渐加深的，遇到一个叶子节点即表示遍历结束
                if(cur->left == nullptr && cur->right == nullptr) {
                    return level;
                }
                if(cur->left != nullptr) q.push(cur->left);
                if(cur->right != nullptr) q.push(cur->right);
            }
        }
        return level;
    }
public:
    int minDepth(TreeNode* root) {
        return traverse(root);
    }
};



