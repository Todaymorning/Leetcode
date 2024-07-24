// Medium
// 654. 最大二叉树
// 给定一个不含重复元素的整数数组。一个以此数组构建的最大二叉树定义如下：
// 二叉树的根是数组中的最大元素。
// 左子树是通过数组中最大值左边部分构造出的最大二叉树。
// 右子树是通过数组中最大值右边部分构造出的最大二叉树。
// 通过给定的数组构建最大二叉树，并且输出这个树的根节点。


#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<unordered_map>
using std::unordered_map;
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return nullptr;
    }
};

// 16:28——16：38
class Solution_D1_M1 {
    TreeNode* traverse(vector<int>& nums, int begin, int end) {
        if(begin == end) return nullptr;
        // 找到子数组中的最大值
        int root_val = INT_MIN;
        int idx = begin;
        for(int i=begin; i<end; i++) {
            int temp = nums[i];
            if(temp > root_val) {
                root_val = temp;
                idx = i;
            }
        }
        TreeNode* root = new TreeNode(root_val);
        root->left = traverse(nums, begin, idx);
        root->right = traverse(nums, idx + 1, end);
        return root;
    }
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int size  = nums.size();
        return traverse(nums, 0, size);
    }
};