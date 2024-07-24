// 968. 监控二叉树
// 思路
// 困难
// 给定一个二叉树，我们在树的节点上安装摄像头。
// 节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。
// 计算监控树的所有节点所需的最小摄像头数量。

// 示例 1：
// 输入：[0,0,null,0,0]
// 输出：1
// 解释：如图所示，一台摄像头足以监控所有节点。

// 示例 2：
// 输入：[0,0,null,0,null,0,null,null,0]
// 输出：2
// 解释：需要至少两个摄像头来监视树的所有节点。 上图显示了摄像头放置的有效位置之一。

// 提示：
// 给定树的节点数的范围是 [1, 1000]。
// 每个节点的值都是 0。



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
    int minCameraCover(TreeNode* root) {

    }
};


// 11:18--11:25(读题找思路)--11:39(错误：单个节点，下面的树)
// 后序遍历，在中间节点上放一个，如果其子节点有监视器的话不用放
// 输入
// root =
// [0,0,0,null,null,null,0]
// 输出
// 1
// 预期结果
// 2
////////////////////////////////////////////////////////////////////// 通过：121/171
// 输入
// root =
// [0,0,null,null,0,0,null,null,0,0]

// 添加到测试用例
// 输出
// 3
// 预期结果
// 2
#if 0
class Solution {
    int result = 0;
    bool isLeaf(TreeNode* node) {
        if(node != nullptr && node->left == nullptr && node->right == nullptr) return true;
        return false;
    }
    bool traversal(TreeNode* root) {
        // 当前节点是叶子节点的时候不需要放
        if(isLeaf(root)) return false;
        bool leftHasd = false;
        bool rightHasd = false;
        // 前序位置
        if(root->left != nullptr) leftHasd = traversal(root->left);
        // 中序位置
        if(root->right != nullptr) rightHasd = traversal(root->right);
        // 后序位置
        if(!leftHasd && !rightHasd) {   // 左右子节点都没有的时候，当前节点给一个
            result++;
            return true;
        }
        else if(isLeaf(root->left) ^ isLeaf(root->right)) { // 只有一个子节点为叶子节点时，当前节点给一个
            result++;
            return true;
        }
        else {
            return false;
        }
    }
public:
    int minCameraCover(TreeNode* root) {
        if(root == nullptr) return 0;
        if(root->left == nullptr && root->right == nullptr) return 1;
        traversal(root);
        return result;
    }
};
#endif




// 所以我们要从下往上看，局部最优：让叶子节点的父节点安摄像头，所用摄像头最少，整体最优：全部摄像头数量所用最少！
// 此时，大体思路就是从低到上，先给叶子节点父节点放个摄像头，然后隔两个节点放一个摄像头，直至到二叉树头结点。
// 此时这道题目还有两个难点：
// 二叉树的遍历
// 如何隔两个节点放一个摄像
// 每个节点可能有几种状态：
// 0：该节点无覆盖
// 1：本节点有摄像头
// 2：本节点有覆盖
// 所以空节点的状态只能是有覆盖，这样就可以在叶子节点的父节点放摄像头了
// 情况 1：左右节点都有覆盖
// 情况 2：左右节点至少有一个无覆盖的情况
// 情况 3：左右节点至少有一个有摄像头
// 情况 4：头结点没有覆盖

// 16:04(看了部分 D1 的思路)--16:29(报错)--16:43(单独一个节点)
// 后序遍历
// 00, 01, 02, 11, 12, 22
// 时间复杂度: O (n)，需要遍历二叉树上的每个节点
// 空间复杂度: O (n)
class Solution {
    int result = 0;
    int traversal(TreeNode* root) {
        if(root == nullptr) return 2;   // 空节点有覆盖
        int leftF = traversal(root->left);
        int rightF = traversal(root->right);
        // 后序位置
        // 22
        if(leftF == 2 && rightF == 2) return 0; // 叶子节点，返回 0，该节点无覆盖
        // 00，01，02
        if(leftF == 0 || rightF == 0) { // 该节点有叶子节点，需要放置一个相机
            result++;
            return 1;
        }
        // 11
        if(leftF == 1 && rightF == 1) return 2; // 子节点都有相机，返回 2，已覆盖
        // 12
        return 2;   // 一个子节点有相机，一个子节点有覆盖（或为空），返回 2，已覆盖
    }
public:
    int minCameraCover(TreeNode* root) {
        // 单独一个节点
        // if(root != nullptr && root->left == nullptr && root->right == nullptr) return 1;
        if(traversal(root) == 0) result++;
        return result;
    }
};

