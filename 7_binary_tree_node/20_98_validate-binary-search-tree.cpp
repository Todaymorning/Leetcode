// 98. 验证二叉搜索树
// 中等
// 给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
// 有效二叉搜索树定义如下：
// 节点的左子树只包含 小于 当前节点的数。
// 节点的右子树只包含 大于 当前节点的数。
// 所有左子树和右子树自身必须也是二叉搜索树。

// 提示：
// 树中节点数目范围在 [1, 10^4] 内
// -2^31 <= Node.val <= 2^31 - 1

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
    bool isValidBST(TreeNode* root) {

    }
};

// 22:10
// 8:41——不会——看D1——8：59
// 可以递归中序遍历将二叉搜索树转变成一个数组
// 然后只要比较一下，这个数组是否是有序的，注意二叉搜索树中不能有重复元素。
class Solution_D1 {
    vector<int> vec;
    // 中序遍历数组，左中右
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        traverse(root->left);
        vec.push_back(root->val);   // 将二叉搜索树转换为有序数组
        traverse(root->right);
    }
public:
    bool isValidBST(TreeNode* root) {
        vec.clear(); // 不加这句在leetcode上也可以过，但最好加上
        traverse(root);
        int size = vec.size();
        if(size == 0 || size == 1) return true;
        int i=0;
        while(i < size) {
            if(vec[i] < vec[i+1]) i++;
            else break;
        }
        if(size == i + 1) return true;
        return false;
    }
};


// 在遍历的时候判断
// 写错：
// 陷阱 1
// 不能单纯的比较左节点小于中间节点，右节点大于中间节点就完事了。
// 我们要比较的是 左子树所有节点小于中间节点，右子树所有节点大于中间节点。
// 陷阱 2
// 样例中最小节点 可能是 int 的最小值，如果这样使用最小的 int 来比较也是不行的。
// 此时可以初始化比较元素为 longlong 的最小值。

// 错误代码
// class Solution {
//     bool traverse(TreeNode* root) {
//         if(root == nullptr) return true;
//         if(root->left != nullptr && root->left->val >= root->val) return false;
//         if(root->right != nullptr && root->val >= root->right->val) return false;
//         if(root->left != nullptr && root->right != nullptr)
//             if(root->left->val >= root->val || root->val >= root->right->val)
//                 return false;
//         bool leftB = traverse(root->left);
//         bool rightB = traverse(root->right);
//         return leftB && rightB;
//     }
// public:
//     bool isValidBST(TreeNode* root) {
//         return traverse(root);
//     }
// };


// 递归中序遍历时判断
// 递归问题分解
// 9：30——9：35
class Solution_D2 {
public:
    long long max = LONG_MIN;   // 因为后台测试数据中有int最小值
    // 中序遍历左中右，一直更新最大值，一旦发现 maxVal >= root->val，就返回 false
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) return true;
        bool leftB = isValidBST(root->left);    // 这里可能已经改变了max，所以要中序
        if(root->val <= max) return false;      // 核心代码，更新 max
        else max = root->val;
        bool rightB = isValidBST(root->right);
        return leftB && rightB;
    }
};


// 如果测试数据中有 long long 的最小值
// 不存储额外的比较值，存储前一个节点
class Solution_D2_2 {
public:
    TreeNode* pre = nullptr;
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) return true;
        bool leftB = isValidBST(root->left);
        if(pre != nullptr && pre->val >= root->val) return false;   // 
        pre = root; // 存储前一个节点
        bool rightB = isValidBST(root->right);
        return leftB && rightB;
    }
};



// 栈迭代中序遍历
// 中序：左中右，栈内：右中左
// 比较统一的中序迭代，存前一个节点
class Solution_D3 {
public:
    bool isValidBST(TreeNode* root) {
        if(root == nullptr) return true;
        stack<TreeNode*> stk;
        stk.push(root);
        TreeNode* cur = nullptr;
        TreeNode* pre = nullptr;
        while(!stk.empty()) {
            cur =stk.top();
            if(cur != nullptr) {
                stk.pop();
                if(cur->right != nullptr) stk.push(cur->right);
                stk.push(cur);
                stk.push(nullptr);
                if(cur->left != nullptr) stk.push(cur->left);
            }
            else {
                stk.pop();
                cur = stk.top();
                stk.pop();
                if(pre != nullptr && pre->val >= cur->val) return false;
                pre = cur;
            }
        }
        return true;
    }
};


// 给两个比较的节点
// 这里给了一个节点该比较最大最小值
// 比较的代码放在前中后序都可以
class Solution_L1 {
    bool traverse(TreeNode* root, TreeNode* max, TreeNode* min) {
        if(root == nullptr) return true;
        // 前中后序位置都可以
        if(max != nullptr && root->val >= max->val) return false;
        if(min != nullptr && root->val <= min->val) return false;
        bool leftB = traverse(root->left, root, min);   // 左边更新max，与更小的max进行比较，继承 min，
        bool rightB = traverse(root->right, max, root); // 右边更新min，与更大的min进行比较，继承 max，
        return leftB && rightB;
    }
public:
    bool isValidBST(TreeNode* root) {
        return traverse(root, nullptr, nullptr);
    }
};



// 再背一次
// 往左时 root应该是最大值
// 往右时 root应该是最小值
class Solution_L1_again {
    bool traverse(TreeNode* min, TreeNode* root, TreeNode* max) {
        if(root == nullptr) return true;
        if(min != nullptr && min->val >= root->val) return false;
        if(max != nullptr && max->val <= root->val) return false;
        bool leftB = traverse(max, root->left, root);   // 往左时 root应该是最大值
        bool rightB = traverse(root, root->right, max); // 往右时 root应该是最小值
        return leftB && rightB;
    }
public:
    bool isValidBST(TreeNode* root) {
        return traverse(nullptr, root, nullptr);
    }
};
