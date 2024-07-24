// Easy
// 404. 左叶子之和
// 计算给定二叉树的所有左叶子之和。
// 节点数在 [1, 1000] 范围内
// -1000 <= Node.val <= 1000

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
    int sumOfLeftLeaves(TreeNode* root) {

    }
};






// 16:26——16:39
// 递归遍历增加一个参数，指明当前节点是否是左子树
// 递归路径回溯——用 0 1 记录路径中该节点是否是左节点————————————舍弃
class Solution_M1 {
    int result = 0;   // 初始化
    void traverse(TreeNode* root, bool is_left) {
        if(root == nullptr) return;
        traverse(root->left, true); // 左子树
        traverse(root->right, false);

        // 前、中、后序位置都可以放
        if(is_left) {
            if(root->left == nullptr && root->right == nullptr) {   // 左叶子
                result += root->val;
            }
        }
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        traverse(root, false);
        return result;
    }
};

// 递归问题分解
// 当前节点的左子树的左子叶之和 + 右子树的左子叶之和
// 启发自 D1
class Solution_D1 {
    int traverse(TreeNode* root, bool is_left) {
        if(root == nullptr) return 0;
        int leftS = traverse(root->left, true);
        int rightS = traverse(root->right, false);
        if(is_left) {
            if(root->left == nullptr && root->right == nullptr) {
                return root->val;
            }
        }
        return leftS + rightS;
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        return traverse(root, false);
    }
};


// D1:递归问题分解
// 不加 is_left 参数
class Solution_D1_2 {
    int traverse(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftS = traverse(root->left);
        int rightS = traverse(root->right);
        // 后序位置
        if(root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
            leftS = root->left->val;
        }
        return leftS + rightS;
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        return traverse(root);
    }
};


// ——17:11——
// 栈迭代遍历，前中后序都可以
// 前序：中左右，栈内：右左中
class Solution_D2 {
    int traverse(TreeNode* root) {
        if(root == nullptr) return 0;
        if(root->left == nullptr && root->right == nullptr) return 0;
        stack<TreeNode*> stk;
        stk.push(root);
        TreeNode* cur;
        int result = 0;
        while(!stk.empty()) {
            cur = stk.top();
            if(cur != nullptr) {
                stk.pop();
                if(cur->right != nullptr) stk.push(cur->right); // 右
                if(cur->left != nullptr) stk.push(cur->left);   // 左
                stk.push(cur);
                stk.push(nullptr);                              // 中
            }
            else {
                stk.pop();
                cur = stk.top();
                stk.pop();
                if(cur->left != nullptr && cur->left->left == nullptr && cur->left->right == nullptr) {
                    result += cur->left->val;
                }
            }
        }
        return result;
    }
public:
    int sumOfLeftLeaves(TreeNode* root) {
        return traverse(root);
    }
};


