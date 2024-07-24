// 104. 二叉树的最大深度
// 给定一个二叉树，找出其最大深度。
// 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。


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

// 解法：
// 递归问题分解
// 递归深度回溯
// 队列迭代层序遍历(栈迭代层序遍历)：while for
// 栈迭代遍历（比较统一的迭代）：后序遍历处理之前(depth--之前)栈内才会存的比较深



// 11:12——11:17
// 递归分解问题
// 动态规划
// 函数返回值，根据返回值在后序位置(离开一个节点的时候)处理
class Solution_L2 {
    int depth(TreeNode* root) {
        if(root == nullptr) return 0;
        int left = depth(root->left);
        int right = depth(root->right);
        int max = left > right ? left:right;
        return max + 1;
    }
public:
    int maxDepth(TreeNode* root) {
        int result = 0;
        result = depth(root);
        return result;
    }
};


// 递归 深度回溯
// 改变一个全局变量
// 进入一个节点的时候做一些处理，退出该节点的时候恢复之前的状态——即回溯
class Solution_L1_D1 {
    // 使用 "全局" 变量记录
    int result = 0;
    int depth = 0;
    // 递归遍历二叉树
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        // 前序位置
        depth++;    // 深度加 1
        result = result>depth ? result : depth; // 遍历的过程中记录最大深度
        traverse(root->left);
        traverse(root->right);
        // 后序位置
        depth--;    // 深度减 1
    }
public:
    int maxDepth(TreeNode* root) {
        traverse(root);
        return result;
    }
};



// 层序遍历
// 迭代遍历，用队列
class Solution_D2 {
    int traverse(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        while(!q.empty()) {
            depth++;
            int size = q.size();
            TreeNode* cur;
            for(int i=0; i<size; i++) {
                cur = q.front();
                q.pop();
                if(cur->left != nullptr) q.push(cur->left);
                if(cur->right != nullptr) q.push(cur->right);
            }
        }
        return depth;
    }
public:
    int maxDepth(TreeNode* root) {
        int result;
        result = traverse(root);
        return result;
    }
};