// 235. 二叉搜索树的最近公共祖先
// 中等
// 给定一个二叉搜索树，找到该树中两个指定节点的最近公共祖先。
// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，
// 最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

// 说明:
// 所有节点的值都是唯一的。
// p、q 为不同节点且均存在于给定的二叉搜索树中。

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return nullptr;
    }
};


// 分析
// 利用二叉搜索树左小右大的特性
// 15:15--15:25--错误--改正--15：39
// 虽然能够正常运行，但没有及时停止递归，还是要找到节点，没有充分运用：min<= root <= max是root即为结果
// 更简单和清晰的解法见 L1_D1

class Solution_M1 {
    TreeNode* find(TreeNode* root, int& min, int& max) {
        if(root == nullptr) return root;
        // 前序位置
        // 当前节点是pq中的一个，这里不用接着往下递归了
        if(root->val == min || root->val == max) {
            return root;
        }

        // 利用二叉搜索树的特性，进行必要的递归
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        if(root->val > min)
            left = find(root->left, min, max);
        if(root->val < max)
            right = find(root->right, min, max);

        if(left != nullptr && right != nullptr) {   // *** 
            return root;    // root本身即为公共节点
        }

        return left != nullptr ? left : right;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int min, max;
        // min = min(p->val, q->val)
        // max = max(p->val, q->val)
        if(p->val < q->val) {
            min = p->val;
            max = q->val;
        }
        else {
            min = q->val;
            max = p->val;
        }
        return find(root, min, max);
    }
};


// L1 逻辑更加简化，及时停止递归
class Solution_L1_D1 {
    TreeNode* find(TreeNode* root, int &min, int &max) {
        if(root == nullptr) return root;
        
        if(root->val > max) {
            // 当前节点太大，去左子树找
            return find(root->left, min, max);
        }

        if(root->val < min) {
            // 当前节点太小，去右子树找
            return find(root->right, min, max);
        }

        // min <= root.val <= max
        // 则当前节点就是最近公共祖先
        return root;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int minVal = min(p->val, q->val);
        int maxVal = max(p->val, q->val);
        return find(root, minVal, maxVal);
    }
};


// 迭代法遍历，简化迭代法，不需要栈
// 二叉搜索树，不需要完全遍历，迭代不宜使用传统迭代方式
class Solution_D2_M2 {
    TreeNode* find(TreeNode* root, int &min, int &max) {
        if(root == nullptr) return nullptr;
        while(root != nullptr) {
            if(root->val > max) {
                // 当前节点太大，去左子树找
                root = root->left;
            }
            else if(root->val < min) {
                // 当前节点太小，去右子树找
                root = root->right;
            }
            else {
                return root;
            }
        }
        return nullptr;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int minVal = min(p->val, q->val);
        int maxVal = max(p->val, q->val);
        return find(root, minVal, maxVal);
    }
};

