// 669. 修剪二叉搜索树
// 中等
// 给你二叉搜索树的根节点 root ，同时给定最小边界 low 和最大边界 high。通过修剪二叉搜索树，使得所有节点的值在 [low, high] 中。
// 结果应当返回修剪好的二叉搜索树的新的根节点。注意，根节点可能会根据给定的边界发生改变。
// 修剪树 不应该 改变保留在树中的元素的相对结构 (即，如果没有被移除，原有的父代子代关系都应当保留)。
// 可以证明，存在 唯一的答案 。

// 提示：
// 树中节点数在范围 [1, 10^4] 内
// 0 <= Node.val <= 10^4
// 树中每个节点的值都是 唯一 的
// 题目数据保证输入是一棵有效的二叉搜索树
// 0 <= low <= high <= 10^4


#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<unordered_map>
#include<algorithm> // min() max() sort()
using std::min;
using std::max;
using std::unordered_map;
using std::stack;
using std::vector;
using std::queue;
using std::pair;
using std::sort;
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
    TreeNode* trimBST(TreeNode* root, int low, int high) {

    }
};


// 

// 22:00--22:09 没思路，不会--22：32 写
// 9：25--9:31 错误
#if 0
class Solution_M1 {
    TreeNode* parent = nullptr;
    TreeNode* trim(TreeNode* root, const int& low, const int& high) {
        if(root == nullptr) return root;
        if(root->val < low) parent->left = nullptr;
        if(root->val > low) parent->right = nullptr;

        parent = root;
        root->left = trim(root->left, low, high);
        root->right = trim(root->right, low, high);
        return root;
    }
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(root == nullptr) return root;
        while(root->val < low && root != nullptr) root = root->right;
        while(root->val > high && root != nullptr) root = root->left;
        trim(root, low, high);
        return root;
    }
};
#endif

// 递归，有返回值
class Solution_D1 {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(root == nullptr) return root;
        if(root->val > high) return trimBST(root->left, low, high); // 寻找符合区间[low, high]的节点
        if(root->val < low) return trimBST(root->right, low, high); // 寻找符合区间[low, high]的节点
        root->left = trimBST(root->left, low, high);    // root->left接入符合条件的左孩子
        root->right = trimBST(root->right, low, high);  // root->left接入符合条件的左孩子
        return root;
    }
};


// 10：27--10:56错误--查看D2后修改
// 迭代
class Solution_D2 {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        // 找到符合条件的根节点，处理头结点，让root移动到[low, high] 范围内
        // while(root != nullptr && root->val > high) root = root->left; // ***
        // while(root != nullptr && root->val < low) root = root->right; // ***
        while(root != nullptr && (root->val > high || root->val < low)) {
            if(root->val > high)
                root = root->left;
            else
                root = root->right;
        }
        if(root == nullptr) return root;
        // 修剪
        TreeNode* cur = root;
        // 此时root已经在[low, high] 范围内，处理左孩子元素小于low的情况
        // 如果cur满足要求，更小的在left上，right一定满足要求
        while(cur != nullptr) {
            while(cur->left != nullptr && cur->left->val < low)
                cur->left = cur->left->right;
            cur = cur->left;    // ***
        }
        cur = root;
        // 此时root已经在[low, high] 范围内，处理右孩子大于high的情况
        // 如果cur满足要求，更大的在right上，left一定满足要求
        while(cur != nullptr) {
            while(cur->right != nullptr && cur->right->val > high)
                cur->right = cur->right->left;
            cur = cur->right;
        }
        return root;
    }
};