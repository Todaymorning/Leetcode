// 701. 二叉搜索树中的插入操作
// 中等
// 给定二叉搜索树（BST）的根节点 root 和要插入树中的值 value ，将值插入二叉搜索树。 
// 返回插入后二叉搜索树的根节点。 新值和原始二叉搜索树中的任意节点值都不同。
// 注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。 你可以返回 任意有效的结果。

// 提示：
// 给定的树上的节点数介于 0 和 10^4 之间
// 每个节点都有一个唯一整数值，取值范围从 0 到 10^8
// -10^8 <= val <= 10^8
// 新值和原始二叉搜索树中的任意节点值都不同

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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        return root;
    }
};


// 解法：
// 可以先遍历二叉搜索树，将其变为有序数组后在数组的对应位置插入val，然后再重新构建二叉树
// 带返回值的递归————有选择的递归遍历
// 不带返回值的递归————有选择的递归问题分解


// ~18:26--18:36--18：39（改错）
// 不带返回值的递归
class Solution_M1 {
    void insert(TreeNode* root, int &val) {
        vector<int> aba;
        if(root == nullptr) return;
        // val比当前值小，添加到左子树
        if(root->val > val) {
            if(root->left == nullptr) {
                root->left = new TreeNode(val);
                // return;
            }
            else {
                insert(root->left, val);
            }
        }
        // val比当前值大，添加到左子树
        else {
            if(root->right == nullptr) {
                root->right = new TreeNode(val);
                // return;
            }
            else {
                insert(root->right, val);
            }

        }
    }
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr) return new TreeNode(val);   // 原树为空 ***
        insert(root, val);
        return root;
    }
};


// 18:59--19:14
// 不带返回值的递归，参考D2，看自己能否写出------------总结：该解法实际上和 M1 相同
// 需要借助全局变量 parent
class Solution_D2 {
    TreeNode* parent = nullptr;
    void insert(TreeNode* cur, int &val) {
        if(cur == nullptr) {
            // if(parent == nullptr) // 不会有这种情况
            if(parent->val > val)
                parent->left = new TreeNode(val);
            else
                parent->right = new TreeNode(val);
            return; // 结束递归
        }
        parent = cur;
        // val比当前值小，添加到左子树
        if(cur->val > val) insert(cur->left, val);
        // val比当前值大，添加到左子树
        if(cur->val < val) insert(cur->right, val);
    }
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // root为nullptr
        if(root == nullptr) return new TreeNode(val);
        insert(root, val);
        return root;
    }
};


// 19:14--19:24
// 有返回值的递归
// 有选择的递归问题分解
// 启发自 D1 L1
// 通过递归函数的返回值完成父子节点的赋值可能可以带来便利。
class Solution_D1_L1 {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr) return new TreeNode(val);
        if(root->val > val) root->left = insertIntoBST(root->left, val);
        if(root->val < val) root->right = insertIntoBST(root->right, val);
        return root;
    }
};



// 19:26--19:34----尝试成功
// 迭代
// 对应 Solution_M1
class Solution_D3_M {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr) return new TreeNode(val);
        TreeNode* cur = root;
        while(cur != nullptr) {
            if(cur->val > val) {
                if(cur->left != nullptr)
                    cur = cur->left;
                else {
                    cur->left = new TreeNode(val);
                    break; // 
                }
            }
            if(cur->val < val) {
                if(cur->right != nullptr)
                    cur = cur->right;
                else {
                    cur->right = new TreeNode(val);
                    break; // 
                }
            }
        }
        return root;
    }
};

// 迭代
// 对应 Solution_D2
class Solution_D3_copy {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == NULL) {
            TreeNode* node = new TreeNode(val);
            return node;
        }
        TreeNode* cur = root;
        TreeNode* parent = root; // 这个很重要，需要记录上一个节点，否则无法赋值新节点
        while (cur != NULL) {
            parent = cur;
            if (cur->val > val) cur = cur->left;
            else cur = cur->right;
        }
        TreeNode* node = new TreeNode(val);
        if (val < parent->val) parent->left = node;// 此时是用parent节点的进行赋值
        else parent->right = node;
        return root;
    }
};