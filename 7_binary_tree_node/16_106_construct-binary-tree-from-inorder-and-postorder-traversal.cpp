// Medium
// 106. 从中序与后序遍历序列构造二叉树
// 给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历，
//  postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。

// 1 <= inorder.length <= 3000
// postorder.length == inorder.length
// -3000 <= inorder[i], postorder[i] <= 3000
// inorder 和 postorder 都由 不同 的值组成
// postorder 中每一个值都在 inorder 中
// inorder 保证是树的中序遍历
// postorder 保证是树的后序遍历


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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return nullptr;
    }
};

// 20：11
// 没有思路
// 20：31
// 10:25——10：50——11:01
// 迭代问题分解，传递数组，反复拷贝
class Solution_D1 {
    TreeNode* traverse(vector<int>& inorder, vector<int>& postorder) {
        if(postorder.size() == 0) return nullptr;
        // 找到根节点
        int rootVal = postorder.back();
        TreeNode* root = new TreeNode(rootVal);
        // 在中序中找到根节点的位置
        int rootIdx;
        int size = postorder.size();
        for(rootIdx=0; rootIdx<size; rootIdx++) {
            if(inorder[rootIdx] == rootVal) break;
        }
        // 切割中序数组
        vector<int> inorderL(inorder.begin(), inorder.begin() + rootIdx);
        vector<int> inorderR(inorder.begin() + rootIdx + 1, inorder.end());
        // 切割后序数组
        vector<int> postorderL(postorder.begin(), postorder.begin() + rootIdx);
        vector<int> postorderR(postorder.begin() + rootIdx, postorder.end() - 1);   // 最后一个元素已经用过了
        // 继续迭代
        root->left = traverse(inorderL, postorderL);
        root->right = traverse(inorderR, postorderR);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        TreeNode* root = traverse(inorder, postorder);
        return root;
    }
};


// 11：02——11：41
// 迭代问题分解，传递索引，不用拷贝
// 细节的把控，需要再写一遍
class Solution_D2 {
    vector<int> in;
    vector<int> post;
    TreeNode* traverse(int in_begin, int in_end, int post_begin, int post_end) {
        if(in_begin == in_end) return nullptr;
        // 找到根节点(post最后一个元素)
        int size = in_end - in_begin;
        int root_val = post[post_end - 1];
        TreeNode* root = new TreeNode(root_val);
        // 找到根节点在in中的索引, 注意idx开始值和in的索引方式
        int idx;
        for(idx = 0; idx<size; idx++) {
            if(in[in_begin + idx] == root_val) break;
        }
        // 切割并迭代
        // 中序切割：[in_begin, in_begin+idx)  in_begin+idx  [in_begin+idx+1, in_end)
        // 后序切割：[in_begin, in_begin+idx)  [in_gegin+idx, post_end -1)  post_end
        root->left = traverse(in_begin, in_begin + idx, post_begin, post_begin + idx);
        root->right = traverse(in_begin + idx + 1, in_end, post_begin + idx, post_end - 1);

        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int size = inorder.size();
        if(size == 0) return nullptr;
        in = inorder;
        post = postorder;
        // 索引左闭右开 [0, size)
        return traverse(0, size, 0, size);
    }
};


// 15:00——15:18——15:25
// 迭代问题分解，传递索引，不用拷贝
// 第二遍，左闭右闭
class Solution_D2_2 {
    vector<int> in;
    vector<int> post;
    TreeNode* traverse(int in_begin, int in_end, int post_begin, int post_end) {
        if(in_begin < in_end) return nullptr;   // 分割时没有验证大小，存在子叶为空的情况，所以这里不能省略
        // 就剩一个元素
        if(in_begin == in_end) return new TreeNode(in[in_begin]);
        // 多个元素时，找到 root
        int root_val = post[post_end];
        TreeNode* root = new TreeNode(root_val);
        int idx = 0;
        int size = in_end - in_begin + 1;
        // 找到root位于in中的索引
        for(idx=0; idx<size; idx++) {
            if(in[in_begin + idx] == root_val) break;
        }
        // 切割 in 和 post
        root->left = traverse(in_begin, in_begin + idx - 1, post_begin, post_begin + idx - 1);
        root->right = traverse(in_begin + idx + 1, in_end, post_begin + idx, post_end - 1);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if(inorder.size() == 0) return nullptr;
        in = inorder;
        post = postorder;
        int size = inorder.size();
        return traverse(0, size-1, 0, size-1);
    }
};