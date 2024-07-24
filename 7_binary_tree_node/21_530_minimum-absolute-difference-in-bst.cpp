// 530. 二叉搜索树的最小绝对差
// 简单
// 给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。
// 差值是一个正数，其数值等于两值之差的绝对值。
// 提示
// 树中节点的数目范围是 [2, 10^4]
// 0 <= Node.val <= 10^5

#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<unordered_map>
#include<algorithm> // min() max()
using std::min;
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
    int getMinimumDifference(TreeNode* root) {
        return INT_MAX;
    }
};

// 递归中序遍历变成有序数组后做差比较：占用空间大
// 递归中序遍历时比较——全局变量存前一个节点或前一个节点的值
// 栈迭代中序遍历时比较——..


// 14:50--15:00--15:07
// 递归中序遍历的时候比较
// 用两个全局变量记录结果和前一个节点的值
class Solution_M1 {
    int diff = INT_MAX;
    int pre_val = -1;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        traverse(root->left);
        if(diff == -1) pre_val = root->val;
        else if(diff > abs(pre_val - root->val)) {
            diff = abs(pre_val - root->val);
        }
        pre_val = root->val;
        traverse(root->right);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        traverse(root);
        return diff;
    }
};


// 递归中序遍历的时候比较
// 用两个全局变量记录结果和前一个节点
class Solution_D2_copy {
private:
    int result = INT_MAX;
    TreeNode* pre = NULL;
    void traversal(TreeNode* cur) {
        if (cur == NULL) return;
        traversal(cur->left);   // 左
        if (pre != NULL){       // 中
            result = min(result, cur->val - pre->val);
        }
        pre = cur; // 记录前一个
        traversal(cur->right);  // 右
    }
public:
    int getMinimumDifference(TreeNode* root) {
        traversal(root);
        return result;
    }
};




// 将二叉搜索树转化为有序数组后比较
class Solution_D1_copy {
private:
    vector<int> vec;
    void traversal(TreeNode* root) {
        if (root == NULL) return;
        traversal(root->left);
        vec.push_back(root->val); // 将二叉搜索树转换为有序数组
        traversal(root->right);
    }
public:
    int getMinimumDifference(TreeNode* root) {
        vec.clear();    // 不加也可以，最好加上
        traversal(root);
        if (vec.size() < 2) return 0;
        int result = INT_MAX;
        for (int i = 1; i < int(vec.size()); i++) { // 统计有序数组的最小差值
            result = min(result, vec[i] - vec[i-1]);
        }
        return result;
    }
};


// 15:20--15:29
// 栈迭代中序遍历，比较统一的迭代
// 变量记录差和前一个节点的地址
class Solution_D3_M2 {
    int traverse(TreeNode* root) {
        // if(root == nullptr) return INT_MAX;  // 至少有两个节点
        stack<TreeNode*> s;
        s.push(root);
        TreeNode* cur;
        TreeNode* pre = nullptr;
        int result = INT_MAX;
        while(!s.empty()) {
            cur = s.top();
            if(cur != nullptr) {
                s.pop();
                if(cur->right != nullptr) s.push(cur->right);
                s.push(cur);
                s.push(nullptr);
                if(cur->left != nullptr) s.push(cur->left);
            }
            else {
                s.pop();
                cur = s.top();
                s.pop();
                if(pre != nullptr) {
                    int temp = abs(pre->val - cur->val);
                    result = result < temp ? result : temp;
                }
                pre = cur;  // 放在后面
            }
        }
        return result;
    }
public:
    int getMinimumDifference(TreeNode* root) {
        return traverse(root);
    }
};


