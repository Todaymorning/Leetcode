// Easy
// 112. 路径总和
// 给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，
// 这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。
// 说明：叶子节点是指没有子节点的节点。


#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using std::stack;
using std::vector;
using std::queue;
using std::pair;
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
    bool hasPathSum(TreeNode* root, int targetSum) {

    }
};


// 8:49——8:56
// 递归路径回溯
// 判断返回路径上节点值之和
class Solution_M1 {
    int sum;
    int target;
    bool result = false;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        sum += root->val;   // depth++
        if(root->left == nullptr && root->right == nullptr) {   // 子叶节点
            if(sum == target) {
                result = true;  // 满足要求
            }
        }
        traverse(root->left);
        traverse(root->right);
        sum -= root->val;   // depth--
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        target = targetSum;
        traverse(root);
        return result;
    }
};


// 8:57——9：07
// 递归路径回溯
// 判断返回路径上节点值之和
// 不用全局变量,使用参数传递
class Solution_M2 {
    // sum也可以是引用，这样的话就相当于是全局变量，回溯的时候需要 sum-=root->val;
    void traverse(TreeNode* root, int sum, const int& target, bool& result) {
        if(root == nullptr) return;
        sum += root->val;
        if(root->left == nullptr && root->right == nullptr) {
            if(sum == target) result = true;
            return; // 这里可以直接返回，使用全局变量或引用时不能，因为需要回溯 sum-=root->val
        }
        traverse(root->left, sum, target, result);
        traverse(root->right, sum, target, result);
        // sum-=root->val;  // 如果sum是引用的话这里需要这句话
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        int sum = 0;
        bool result = false;
        traverse(root, sum, targetSum, result);
        return result;
    }
};



// 递归深度回溯
// 递归函数带返回值，不要让空节点进入递归
class Solution_D1 {
    bool traverse(TreeNode* root, int count) {
        if(root->left == nullptr && root->right == nullptr) {
            if(count == 0) return true; // 找到路径
            return false;               // 遇到叶子节点，后面不用继续迭代了
        }
        if(root->left) {
            count -= root->left->val;
            if(traverse(root->left, count)) return true;
            count += root->left->val;
            // if(traverse(root->left, count-=root->left->val)) return true;
        }
        if(root->right) {
            // 这种形式和上面的一样
            if(traverse(root->right, count-=root->right->val)) return true;
        }
        return false;
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return false;   // 在这里判断
        return traverse(root, targetSum-=root->val);
    }
};


// 9:27——9:39
// 递归回溯，递归问题分解(有返回值)
// 因为返回的是bool，因此不能让空节点继续递归
// 启发自 D1
class Solution_D1_2 {
    bool traverse(TreeNode* root, int target) {
        // 节点为空的时候不好确定返回值
        if(root->left == nullptr && root->right == nullptr) {   // 子叶
            if(target-root->val == 0) return true;
            return false;
        }
        int leftB = false;
        int rightB = false;
        if(root->left != nullptr) { // 空节点不入递归，这里其他递归也可以参考
            target -= root->val;
            leftB = traverse(root->left, target);
            target += root->val;
        }
        if(root->right != nullptr) {
            target -= root->val;
            rightB = traverse(root->right, target);
            target += root->val;
        }
        return leftB || rightB;
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return false;
        return traverse(root, targetSum);
    }
};

// 代码精简
class Solution_D1_3 {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        if (!root->left && !root->right && sum == root->val) {
            return true;
        }
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};


// 9:50——10:04
// 栈迭代后序遍历回溯
// 其发自D2
// 后序：左右中，栈内：中右左
class Solution_D2_M3 {
    bool traverse(TreeNode* root, int target) {
        if(root == nullptr) return false;
        stack<TreeNode*> stk;
        stk.push(root);
        TreeNode* cur;
        int sum = 0;
        while(!stk.empty()) {
            cur = stk.top();
            // 后序遍历
            if(cur != nullptr) {
                sum += cur->val;    // depth++
                stk.pop();
                stk.push(cur);                                  // 中
                stk.push(nullptr);
                if(cur->right != nullptr) stk.push(cur->right); // 右
                if(cur->left != nullptr) stk.push(cur->left);   // 左
            }
            else {
                stk.pop();
                cur = stk.top();
                stk.pop();
                if(cur->left == nullptr && cur->right == nullptr) { // 子叶
                    if(sum == target) return true;
                }
                sum -= cur->val;    // depth--
            }
        }
        return false;
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        return traverse(root, targetSum);
    }
};


// 11:30——12:00
// 栈迭代回溯通用方法————借用pair
// 启发自 D2
// 前序：中左右，栈内：右左中
// 中序：左中右，栈内：右中左
// 后序：左右中，栈内：中右左
class Solution_D2_M4 {
    bool traverse(TreeNode* root, int target) {
        if(root == nullptr) return false;
        stack<pair<TreeNode*, int>> stk;
        // pair的第二个元素记录了走过的路径中所有元素之和，不包括自身(初始化为 0 )
        // 判断的时候需要加上当前节点的元素
        stk.push(pair<TreeNode*, int>(root, 0));    // ***
        pair<TreeNode*, int> cur;
        int sum = 0;
        while(!stk.empty()) {
            cur = stk.top();
            // 前序遍历
            if(cur.first != nullptr) {
                stk.pop();
                if(cur.first->right != nullptr)
                    stk.push(pair<TreeNode*, int>(cur.first->right, cur.first->val + cur.second));   // 右 ***
                if(cur.first->left != nullptr)
                    stk.push(pair<TreeNode*, int>(cur.first->left, cur.first->val + cur.second));    // 左 ***
                stk.push(cur);                                                                      // 中
                stk.push(pair<TreeNode*, int>(nullptr, 0));
            }
            else {
                stk.pop();
                cur = stk.top();
                stk.pop();
                // 判断时加上节点自身的元素
                if(cur.first->left == nullptr && cur.first->right == nullptr) { // 子叶
                    if(cur.first->val + cur.second == target) return true;
                }
            }
        }
        return false;
    }
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        return traverse(root, targetSum);
    }
};


