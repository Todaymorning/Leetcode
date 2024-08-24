// https://leetcode.cn/problems/diameter-of-binary-tree/description/?envType=study-plan-v2&envId=top-100-liked
// 543. 二叉树的直径
// 已解答
// 简单
// 相关标签
// 相关企业
// 给你一棵二叉树的根节点，返回该树的 直径 。

// 二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。

// 两节点之间路径的 长度 由它们之间边数表示。

 

// 示例 1：


// 输入：root = [1,2,3,4,5]
// 输出：3
// 解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。
// 示例 2：

// 输入：root = [1,2]
// 输出：1
 

// 提示：

// 树中节点数目在范围 [1, 104] 内
// -100 <= Node.val <= 100



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



class Solution {
    int res;
    // 返回深度 / 层数
    int depth(TreeNode* root) {
        if(root == nullptr) return 0;
        int left = depth(root->left);
        int right = depth(root->right);

        res = std::max(left + right, res);

        return std::max(left, right) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        // 2024年8月6日
        // 23:05--23:18
        res = 0;
        depth(root);
        return res;
    }
};
