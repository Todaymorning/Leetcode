// 108. 将有序数组转换为二叉搜索树
// 简单
// 给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡 二叉搜索树。
// 高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。

// 提示：
// 1 <= nums.length <= 10^4
// -10^4 <= nums[i] <= 10^4
// nums 按 严格递增 顺序排列

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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return nullptr;
    }
};



// 15:15--15:24--15:31(改错)
// 有返回值的递归，传递数组
class Solution_M1 {
    TreeNode* buildBST(vector<int>& nums) {
        int size = nums.size();
        int mid = size/2;
        TreeNode* root = new TreeNode(nums[mid]);
        if(size == 1) return root;
        if(size == 2) {
            root->left = new TreeNode(nums[0]);
            return root;
        }
        // vector<int> left(mid, 0);
        // for(int i=0; i<mid; i++) {
        //     left[i] = nums[i];
        // }
        vector<int> left(nums.begin(), nums.begin() + mid);
        vector<int> right(nums.begin() + mid + 1, nums.end());  // ***
        root->left = buildBST(left);
        root->right = buildBST(right);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildBST(nums);
    }
};


// 15:31--15:39--15:56(改错)
// 有返回值的递归，传递索引
// 左闭右开
class Solution_M2 {
    TreeNode* buildBST(vector<int>& nums, int begin, int end) {
        if(begin >= end) return nullptr;
        int size = end - begin;
        int mid = begin + size / 2; // ***
        TreeNode* root = new TreeNode(nums[mid]);
        if(size == 1) return root;
        root->left = buildBST(nums, begin, mid);
        root->right = buildBST(nums, mid + 1, end);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildBST(nums, 0, nums.size());  // 左闭右开
    }
};


// 15:58--16:09
// 有返回值的递归
// 传递索引，左闭右闭
// 当数组是偶数的时候 mid = begin + (end - begin)/2 选取的是左边的中间值作为根节点
//                  mid = begin + (end - begin + 1) / 2 选取的是右边的中间值作为根节点
class Solution_M3 {
    TreeNode* buildBST(vector<int>& nums, int begin, int end) {
        if(begin > end) return nullptr; // >
        int size = end - begin + 1;     // +1
        int mid = begin + size/2;   // 别忘了加上初始值
        TreeNode* root = new TreeNode(nums[mid]);
        if(size == 1) return root;
        root->left = buildBST(nums, begin, mid - 1);
        root->right = buildBST(nums, mid + 1, end);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return buildBST(nums, 0, nums.size() - 1);
    }
};





class Solution_D1_copy {
private:
    TreeNode* traversal(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = left + ((right - left) / 2);  // 取左边的作为根节点 ***
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = traversal(nums, left, mid - 1);
        root->right = traversal(nums, mid + 1, right);
        return root;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = traversal(nums, 0, nums.size() - 1); // ***
        return root;
    }
};



// 没看
class Solution_D2_copy {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.size() == 0) return nullptr;

        TreeNode* root = new TreeNode(0);   // 初始根节点
        queue<TreeNode*> nodeQue;           // 放遍历的节点
        queue<int> leftQue;                 // 保存左区间下标
        queue<int> rightQue;                // 保存右区间下标
        nodeQue.push(root);                 // 根节点入队列
        leftQue.push(0);                    // 0为左区间下标初始位置
        rightQue.push(nums.size() - 1);     // nums.size() - 1为右区间下标初始位置

        while (!nodeQue.empty()) {
            TreeNode* curNode = nodeQue.front();
            nodeQue.pop();
            int left = leftQue.front(); leftQue.pop();
            int right = rightQue.front(); rightQue.pop();
            int mid = left + ((right - left) / 2);

            curNode->val = nums[mid];       // 将mid对应的元素给中间节点

            if (left <= mid - 1) {          // 处理左区间
                curNode->left = new TreeNode(0);
                nodeQue.push(curNode->left);
                leftQue.push(left);
                rightQue.push(mid - 1);
            }

            if (right >= mid + 1) {         // 处理右区间
                curNode->right = new TreeNode(0);
                nodeQue.push(curNode->right);
                leftQue.push(mid + 1);
                rightQue.push(right);
            }
        }
        return root;
    }
};