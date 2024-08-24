// https://leetcode.cn/problems/binary-tree-maximum-path-sum/description/
// 124. 二叉树中的最大路径和
// 已解答
// 困难
// 相关标签
// 相关企业
// 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

// 路径和 是路径中各节点值的总和。

// 给你一个二叉树的根节点 root ，返回其 最大路径和 。

 

// 示例 1：


// 输入：root = [1,2,3]
// 输出：6
// 解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
// 示例 2：


// 输入：root = [-10,9,20,null,null,15,7]
// 输出：42
// 解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
 

// 提示：

// 树中节点数目范围是 [1, 3 * 104]
// -1000 <= Node.val <= 1000


#include<iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int maxPathSum(TreeNode* root) {

    }
};


class Solution_M1 {
    int res = INT_MIN;
    int traverse(TreeNode* root) {
        if(root == nullptr) return 0;
        int left = std::max(traverse(root->left), 0);
        int right = std::max(traverse(root->right), 0);
        res = std::max(res, root->val + left + right);
        return root->val + std::max(left, right);
    }
public:
    int maxPathSum(TreeNode* root) {
        traverse(root);
        return res;
    }
};




// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1 {
    int res = INT_MIN;

public:
    int maxPathSum(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        // 计算单边路径和时顺便计算最大路径和
        oneSideMax(root);
        return res;
    }

    // 定义：计算从根节点 root 为起点的最大单边路径和
    int oneSideMax(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftMaxSum = std::max(0, oneSideMax(root->left));
        int rightMaxSum = std::max(0, oneSideMax(root->right));
        // 后序遍历位置，顺便更新最大路径和
        int pathMaxSum = root->val + leftMaxSum + rightMaxSum;
        res = std::max(res, pathMaxSum);
        // 实现函数定义，左右子树的最大单边路径和加上根节点的值
        // 就是从根节点 root 为起点的最大单边路径和
        return std::max(leftMaxSum, rightMaxSum) + root->val;
    }
};