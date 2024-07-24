// Easy:
// 257. 二叉树的所有路径
// 给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。
// 给定一个二叉树，返回所有从根节点到叶子节点的路径。
// 说明：叶子节点是指没有子节点的节点。


#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<string>
using std::stack;
using std::vector;
using std::queue;
using std::string;
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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> s;
        return s;
    }
};



// 11:42——12:26
// 递归分解问题——————————————有错误
class Solution_M1 {
    vector<string> result;
    bool traverse(TreeNode* root) {
        if(root == nullptr) return false;
        bool leftB = traverse(root->left);
        bool rightB = traverse(root->right);
        // 后序位置
        // 该节点有叶子节点
        if(leftB || rightB) {
            for(int i=0; i<result.size(); i++) {
                result[i] = std::to_string(root->val) + "->" + result[i];
            }
        }
        // 该节点是叶子节点
        if(root->left == nullptr && root->right == nullptr) {
            result.push_back(std::to_string(root->val));
            return true;
        }
        return leftB || rightB;
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        bool hasLeaves = false;
        traverse(root);
        return result;
    }
};




// 思路：
// 这道题目要求从根节点到叶子的路径，所以需要前序遍历，这样才方便让父节点指向孩子节点，找到对应的路径。
// 在这道题目中将第一次涉及到回溯，因为我们要把路径记录下来，需要回溯来回退一个路径再进入另一个路径。


// 递归路径回溯
// 利用回溯记录路径
class Solution_D1 {
    string path = "";
    vector<string> result;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        string temp_path = path;    // 保存临时路径
        path = path + std::to_string(root->val) + "->"; // 当前路径 depth++，进入下一层要用的path
        traverse(root->left);
        traverse(root->right);
        if(root->left == nullptr && root->right == nullptr) {   // 是叶子节点时
            result.push_back(temp_path + std::to_string(root->val));
        }
        path = temp_path;           // 恢复路径 depth--
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        traverse(root);
        return result;
    }
};


// 15:36——15:51
// 递归节点值回溯
// 利用回溯记录路径中每个节点的值，然后拼接成字符串
class Solution {
    vector<string> result;
    vector<string> path;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        path.push_back(std::to_string(root->val));  // depth++
        traverse(root->left);
        traverse(root->right);
        if(root->left == nullptr && root->right == nullptr) {
            int size = path.size();
            string temp = path[0];
            for(int i=1; i<size; i++) {

                temp = temp + "->" + path[i];
            }
            result.push_back(temp);
        }
        path.pop_back();            // depth--
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        traverse(root);
        return result;
    }
};



// 16:03——16:21
// 迭代法节点值回溯
// 后序遍历：左右中，栈内顺序 中右左
class Solution {
    vector<string> result;
    vector<int> path;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        stack<TreeNode*> stk;
        TreeNode* cur;
        stk.push(root);
        while(!stk.empty()) {
            cur = stk.top();
            if(cur != nullptr) {
                path.push_back(cur->val);   // depth++
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
                if(cur->left == nullptr && cur->right == nullptr) { // 叶子节点时
                    string temp = std::to_string(path[0]);
                    int size = path.size();
                    for(int i=1; i<size; i++) {
                        temp = temp + "->" + std::to_string(path[i]);
                    }
                    result.push_back(temp);
                }
                path.pop_back();            // depth--
            }
        }

    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        traverse(root);
        return result;
    }
};
