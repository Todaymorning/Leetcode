// 450. 删除二叉搜索树中的节点
// 中等
// 给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。
// 返回二叉搜索树（有可能被更新）的根节点的引用。
// 一般来说，删除节点可分为两个步骤：
// 首先找到需要删除的节点；
// 如果找到了，删除它。


// 提示:
// 节点数的范围 [0, 10^4].
// -10^5 <= Node.val <= 10^5
// 节点值唯一
// root 是合法的二叉搜索树
// -10^5 <= key <= 10^5


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

// 


class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {

    }
};



// 19:53--20:02(分析)--20:26(写)--20:58(改)
// 分析：
// 找到 val
// val对应的节点是叶子节点(cur->left = cur->right = nullptr)，从父节点删掉即可
// 找到value，val的右变父，左变父最左
// 有返回值的递归
//
// 总结：
// 有以下五种情况：
// 第一种情况：没找到删除的节点，遍历到空节点直接返回了
// 找到删除的节点
// 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回 NULL为根节点
// 第三种情况：删除节点的左孩子为空，右孩子不为空，删除节点，右孩子补位，返回右孩子为根节点
// 第四种情况：删除节点的右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
// 第五种情况：左右孩子节点都不为空，则将删除节点的左子树头结点（左孩子）放到删除节点的右子树的最左面节点的左孩子上，
// 返回删除节点右孩子为新的根节点。
class Solution_M1 {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) return root;
        if(root->val == key) {
            // if(parent == nullptr) return nullptr;   // 根节点就是key ***
            if(root->left == nullptr || root->right == nullptr) {           // ***
                root = root->left != nullptr ? root->left : root->right;    // ***
                return root;                                                // *** 
            }
            TreeNode* temp = root->left;
            // 右变父
            root = root->right;     // 要返回的 root
            // 左变最左
            TreeNode* cur = root;
            while(cur->left != nullptr) {
                cur = cur->left;
            }
            cur->left = temp;
            return root;    // 不用继续递归了
        }
        if(root->val > key) root->left = deleteNode(root->left, key);
        if(root->val < key) root->right = deleteNode(root->right, key);
        return root;
    }
};


// 与 M1相比更为详细
// 有返回值的递归
class Solution_D1_copy {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root; // 第一种情况：没找到删除的节点，遍历到空节点直接返回了
        // 找到节点
        if (root->val == key) {
            // 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
            if (root->left == nullptr && root->right == nullptr) {
                ///! 内存释放
                delete root;
                return nullptr;
            }
            // 第三种情况：其左孩子为空，右孩子不为空，删除节点，右孩子补位 ，返回右孩子为根节点
            else if (root->left == nullptr) {
                auto retNode = root->right;
                ///! 内存释放
                delete root;
                return retNode;
            }
            // 第四种情况：其右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
            else if (root->right == nullptr) {
                auto retNode = root->left;
                ///! 内存释放
                delete root;
                return retNode;
            }
            // 第五种情况：左右孩子节点都不为空，则将删除节点的左子树放到删除节点的右子树的最左面节点的左孩子的位置
            // 并返回删除节点右孩子为新的根节点。
            else {
                TreeNode* cur = root->right; // 找右子树最左面的节点
                while(cur->left != nullptr) {
                    cur = cur->left;
                }
                cur->left = root->left; // 把要删除的节点（root）左子树放在cur的左孩子的位置
                TreeNode* tmp = root;   // 把root节点保存一下，下面来删除
                root = root->right;     // 返回旧root的右孩子作为新root
                delete tmp;             // 释放节点内存（这里不写也可以，但C++最好手动释放一下吧）
                return root;
            }
        }
        if (root->val > key) root->left = deleteNode(root->left, key);
        if (root->val < key) root->right = deleteNode(root->right, key);
        return root;
    }
};

// 交换目标值和其右子树左下角的值，然后再次碰到的时候删除
// 该方法对普通二叉树也可以使用
class Solution_D2_copy {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;
        if (root->val == key) {
            if (root->right == nullptr) { // 这里第二次操作目标值：最终删除的作用
                return root->left;
                // auto temp = root->left;
                // delete temp;
                // return temp;
            }
            TreeNode *cur = root->right;
            while (cur->left) { // 找到右子树的左下角(右子树最小值)
                cur = cur->left;
            }
            std::swap(root->val, cur->val); // 这里第一次操作目标值：交换目标值其右子树最左面节点。
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
};


// 迭代法
class Solution_D3_copy {
private:
    // 将目标节点（删除节点）的左子树放到 目标节点的右子树的最左面节点的左孩子位置上
    // 并返回目标节点右孩子为新的根节点
    TreeNode* deleteOneNode(TreeNode* target) {
        if (target == nullptr) return target;
        if (target->right == nullptr) return target->left;  // 没delete
        TreeNode* cur = target->right;
        while (cur->left) {
            cur = cur->left;
        }
        cur->left = target->left;
        return target->right;
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;
        TreeNode* cur = root;
        TreeNode* pre = nullptr; // 记录cur的父节点，用来删除cur
        while (cur) {   // 找到 key 节点
            if (cur->val == key) break;
            pre = cur;
            if (cur->val > key) cur = cur->left;
            else cur = cur->right;
        }
        if (pre == nullptr) { // 如果搜索树只有头结点
            return deleteOneNode(cur);
        }
        // pre 要知道是删左孩子还是右孩子
        if (pre->left && pre->left->val == key) {
            pre->left = deleteOneNode(cur);
        }
        if (pre->right && pre->right->val == key) {
            pre->right = deleteOneNode(cur);
        }
        return root;
    }
};
