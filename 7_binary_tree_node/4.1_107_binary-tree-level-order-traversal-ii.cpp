// 107. 二叉树的层次遍历 II
// 给定一个二叉树，返回其节点值自底向上的层次遍历。
//（即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using std::vector;
using std::queue;
using std::reverse;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


// 16:16-16:35
// 递归法：先获取层序遍历，然后再调换次序
class Solution_D1 {
    void order(TreeNode* root, vector<vector<int>>& result, int depth) {
        if(root == nullptr) return;
        if(depth == int(result.size())) result.push_back(vector<int>());
        result[depth].push_back(root->val);
        order(root->left, result, depth + 1);
        order(root->right, result, depth + 1);
    }
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        vector<vector<int>> temp;
        order(root, temp, 0);       // 正序层级遍历
        int size = temp.size();
        for(int i=0; i<size; i++) { // 反序
            result.push_back(temp[size-1-i]);
        }
        // reverse(result.begin(), result.end());
        return result;
    }
};




// 16:39-16.50-17:00
// 迭代法：先获取层次遍历，然后再反向
// 犯的错误：while的条件，没有弹出q
// 也可以使用临时vector,这样就不用depth了
// vector<int> temp
// temp.push_back(cur->left)
class Solution_D2 {
    void order(TreeNode* root, vector<vector<int>>& result) {
        if(root == nullptr) return;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        // while控制层数
        while(!q.empty()) { // !!!!!!!!!!!!!
            int size = q.size();
            result.push_back(vector<int>(size, 0)); // 添加新的一行
            // for遍历每一层
            for(int i=0; i<size; i++) {
                TreeNode* cur = q.front();
                q.pop();    // 弹出!!!!!!!!!!!!!!!!!!!!!!!!!
                result[depth][i] = cur->val;
                if(cur->left != nullptr) q.push(cur->left);
                if(cur->right != nullptr) q.push(cur->right);
            }
            depth++;
        }
        reverse(result.begin(), result.end());  // 翻转，这里只翻转行，列没有翻转
    }
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        order(root, result);
        return result;
    }
};