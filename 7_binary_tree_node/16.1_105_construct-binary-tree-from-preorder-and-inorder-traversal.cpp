// Medium
// 105. 从前序与中序遍历序列构造二叉树
// 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，
// 请构造二叉树并返回其根节点。

#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<unordered_map>
using std::unordered_map;
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    
    }
};

// 其他解法
// 可以使用 unordered_map保存值和索引，将for循环变成简单的索引
class temp {
    vector<int> preorder, inorder;
    unordered_map<int, int> umap;
    void insert() {
        for(int i=0; i<inorder.size(); i++) {
            umap[inorder[i]] = i;
        }
    }
};

// 15:40——15:54——16:05
// 递归问题分解
// 前序第一个为root，找到中序root索引，以此先分割中序再分割前序
// 左闭右开
class Solution_D1 {
    vector<int> pre;
    vector<int> in;
    TreeNode* traverse(int pre_begin, int pre_end, int in_begin, int in_end) {
        if(pre_begin == pre_end) return nullptr;
        // 根节点
        int root_val = pre[pre_begin];  // 这里不能是 0 ***
        TreeNode* root = new TreeNode(root_val);
        // 根节点在in中的索引
        int size = pre_end - pre_begin;
        int idx;
        for(idx=0; idx<size; idx++) {
            if(in[in_begin + idx] == root_val) break;
        }
        // 分割后递归，左闭右开
        root->left = traverse(pre_begin + 1, pre_begin + 1 + idx, in_begin, in_begin + idx);
        root->right = traverse(pre_begin + 1 + idx, pre_end, in_begin + idx + 1, in_end);

        return root;

    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pre = preorder;
        in = inorder;
        int size = preorder.size();
        return traverse(0, size, 0, size);
    }
};


