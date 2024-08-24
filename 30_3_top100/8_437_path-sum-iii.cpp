// https://leetcode.cn/problems/path-sum-iii/description/?envType=study-plan-v2&envId=top-100-liked
// 437. 路径总和 III
// 尝试过
// 中等
// 相关标签
// 相关企业
// 给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

// 路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

 

// 示例 1：



// 输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
// 输出：3
// 解释：和等于 8 的路径有 3 条，如图所示。
// 示例 2：

// 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
// 输出：3
 

// 提示:

// 二叉树的节点个数的范围是 [0,1000]
// -109 <= Node.val <= 109 
// -1000 <= targetSum <= 1000 


#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x):val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};



// 深度优先遍历，dfs，前缀和
// 前缀和定义：一个节点的前缀和就是该节点到根之间的路径和。
// 用它干什么：两节点间的路径和 = 两节点的前缀和之差
// HashMap存的是什么：前缀和数组
// 恢复状态代码的意义：换路径了，需要恢复

// 节点1的前缀和为: 1
// 节点3的前缀和为: 1 + 2 + 3 = 6
// prefix(3) - prefix(1) == 5
// 所以 节点1 到 节点3 之间有一条符合要求的路径( 2 --> 3 )

class Solution {
public:
    unordered_map<long long, int> prefix;

    int dfs(TreeNode *root, long long curr, int targetSum) {
        if (!root) {
            return 0;
        }

        int ret = 0;
        curr += root->val;  // 计算前缀和
        if (prefix.count(curr - targetSum)) {   // 查找路径
            ret = prefix[curr - targetSum];
        }

        prefix[curr]++;     // 加入前缀和
        ret += dfs(root->left, curr, targetSum);
        ret += dfs(root->right, curr, targetSum);
        prefix[curr]--;     // 回退

        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        prefix[0] = 1;  // ***
        return dfs(root, 0, targetSum);
    }
};


