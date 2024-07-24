// Middle
// 给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。
// 叶子节点 是指没有子节点的节点。

// 其他解法
// 也可以尝试 14 中的 M3、M4

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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {

    }
};


// ——15:30
// 递归路径回溯
// 遍历
// 记录当前的路径
// 可以使用全局变量，也可以当作参数传递
class Solution_D1_M1 {
    vector<vector<int>> result;
    vector<int> path;
    int sum = 0;
    void traverse(TreeNode* root, const int& targetSum) {
        if(root == nullptr) return;
        
        sum += root->val;
        path.push_back(root->val);

        if(root->left == nullptr && root->right == nullptr) {
            if(sum == targetSum) result.push_back(path);
        }

        traverse(root->left, targetSum);
        traverse(root->right, targetSum);

        sum -= root->val;
        path.pop_back();
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        traverse(root, targetSum);
        return result;
    }
};



// 15:30——15:41——15:56
// 递归问题分解
// 这样好像copy的次数过多，不推荐使用
// 可以将用于回溯的 path 和 sum 当作参数（非引用），这样不用在返回的时候单独处理回溯部分
class Solution_M2 {
    vector<int> path;
    int sum = 0;
    vector<vector<int>> traverse(TreeNode* root, const int & targetSum) {
        vector<vector<int>> result;
        path.push_back(root->val);
        sum += root->val;
        if(root->left == nullptr && root->right == nullptr) {
            if(sum == targetSum) {
                result.push_back(path);
                sum -= root->val;   //
                path.pop_back();    //
                return result;  // 返回前要注意回溯部分
            }
        }
        vector<vector<int>> leftP;
        vector<vector<int>> rightP;
        if(root->left != nullptr)
            leftP = traverse(root->left, targetSum);
        if(root->right != nullptr)
            rightP = traverse(root->right, targetSum);
        sum -= root->val;
        path.pop_back();
        int size = rightP.size();
        for(int i=0; i<size; i++) {
            leftP.push_back(rightP[i]);
        }
        return leftP;
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> result;
        if(root == nullptr) return result;
        result = traverse(root, targetSum);
        return result;
    }
};






