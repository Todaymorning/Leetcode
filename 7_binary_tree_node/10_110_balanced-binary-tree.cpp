// Easy：递归分解问题做错
// 110. 平衡二叉树
// 给定一个二叉树，判断它是否是高度平衡的二叉树。
// 本题中，一棵高度平衡二叉树定义为：一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

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
    bool isBalanced(TreeNode* root) {
        return false;
    }
};


// 20:26——20:44
// 递归 问题分解
// 比较左右节点的高度差
// 求二叉树的最大深度时用的前序遍历
// 求二叉树的最大高度时需要使用后序遍历
class Solution_D1 {
    // 求最大深度，这里需要对其稍加改造
    int getMaxHeight(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftH = getMaxHeight(root->left);
        int rightH = getMaxHeight(root->right);
        int result = 1 + leftH > rightH ? leftH : rightH;
        return result;
    }
    // 如果当前传入节点为根节点的二叉树已经不是二叉平衡树了，还返回高度的话就没有意义了。
    // -1 表示已经不是平衡二叉树了，否则返回值是以该节点为根节点树的高度
    int getHeight(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftH = getHeight(root->left);
        if(leftH == -1) return -1;
        int rightH = getHeight(root->right);
        if(rightH == -1) return -1;
        // 后序位置
        if(abs(leftH - rightH) > 1) {   // 不平衡时返回 -1
            return -1;
        }
        else {                          // 平衡时返回高度
            return 1 + leftH > rightH ? leftH : rightH;
        }
    }
public:
    bool isBalanced(TreeNode* root) {
        return getHeight(root) == -1 ? false : true;
    }
};


// 9:17——9:34
// 两个递归函数，一个递归求高度，一个递归求左右节点
// 可以先定义一个函数，专门用来求高度。
// 这个函数通过栈模拟的后序遍历找每一个节点的高度（其实是通过求传入节点为根节点的最大深度来求的高度）本题的迭代方式可以先定义一个函数，专门用来求高度。
// 这个函数通过栈模拟的后序遍历找每一个节点的高度（其实是通过求传入节点为根节点的最大深度来求的高度）
class Solution_D2 {
    int result = 0;
    int depth = 0;
    // 递归，深度回溯，前序遍历，求当前节点下面最大深度
    // 这里使用的时候需要在一个总节点迭代完毕后将 result 和 depth 置零
    void getDepth(TreeNode* root) {
        if(root == nullptr) return;
        // 前序位置
        depth++;
        result = result > depth ? result : depth;
        getDepth(root->left);
        getDepth(root->right);
        depth--;
    }

public:
    bool isBalanced(TreeNode* root) {
        if(root == nullptr) return true;
        // 前序位置
        result = 0; depth = 0;
        getDepth(root->left); int leftH = result;
        result = 0; depth = 0;
        getDepth(root->right); int rightH = result;
        if(abs(leftH - rightH) > 1) return false;   // 当前节点是否平衡
        // 后序位置
        bool leftB = isBalanced(root->left);
        bool rightB = isBalanced(root->right);      // 左右节点是否平衡

        return leftB && rightB;
    }
};


// 将递归用基于栈的迭代替换
// 栈迭代深度回溯(后序)
// 效率很低，有很多重复的计算。
class Solution_D3 {
    // 栈迭代求深度，也可以用比较统一的迭代，也可以用层序遍历迭代
    // 即求一个节点的最大深度，将该节点看作根节点就可以将该函数转化为 7
    // 后序遍历求高度，前序遍历求深度
    // root节点的最大深度，就是root的高度，所以该部分求深度，高度均可
    // 前序：中、左、右，栈内顺序：右、左、中
    // 中序：左、中、右，栈内顺序：右、中、左
    // 后序：左、右、中，栈内顺序：中、右、左

    // 栈迭代求深度（后序遍历），后序遍历处理之前(depth--之前)栈内才会存的比较深
    int getDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        stack<TreeNode*> stk;
        stk.push(root);
        TreeNode* cur;
        int depth = 0;
        int result = 0;
        while(!stk.empty()) {
            cur = stk.top();
            if(cur != nullptr) {
                // 后序遍历顺序 ??????
                stk.pop();
                depth++;    // 进入一个节点
                stk.push(cur);                          // 中
                stk.push(nullptr);
                if(cur->right != nullptr) stk.push(cur->right);// 右
                if(cur->left != nullptr) stk.push(cur->left); // 左
            }
            else {
                stk.pop();
                cur = stk.top();
                stk.pop();
                depth--;    // 退出一个节点
            }
            result = result > depth ? result : depth;
        }
        return result;
    }
public:
    // 前中后序都可
    bool isBalanced(TreeNode* root) {
        if(root == nullptr) return true;
        stack<TreeNode*> stk;
        stk.push(root);
        TreeNode* cur;
        while(!stk.empty()) {
            cur = stk.top();
            stk.pop();  // 在这里pop或在if else中pop
            if(cur != nullptr) {
                if(cur->right != nullptr) stk.push(cur->right);
                if(cur->left != nullptr) stk.push(cur->left);
                stk.push(cur);
                stk.push(nullptr);
            }
            else {
                // stk.pop();
                cur = stk.top();
                stk.pop();
                int leftH = getDepth(cur->left);
                int rightH = getDepth(cur->right);
                if(abs(leftH - rightH) > 1) return false;
            }
        }
        return true;
    }
};
