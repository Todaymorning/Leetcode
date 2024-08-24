// https://leetcode.cn/problems/flatten-binary-tree-to-linked-list/submissions/557042132/
// 114. 二叉树展开为链表
// 已解答
// 中等
// 相关标签
// 相关企业
// 提示
// 给你二叉树的根结点 root ，请你将它展开为一个单链表：

// 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
// 展开后的单链表应该与二叉树 先序遍历 顺序相同。
 

// 示例 1：


// 输入：root = [1,2,5,3,4,null,6]
// 输出：[1,null,2,null,3,null,4,null,5,null,6]
// 示例 2：

// 输入：root = []
// 输出：[]
// 示例 3：

// 输入：root = [0]
// 输出：[0]
 

// 提示：

// 树中结点数在范围 [0, 2000] 内
// -100 <= Node.val <= 100
 

// 进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？



#include<iostream>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution {
public:
    void flatten(TreeNode* root) {

    }
};

class Solution_M1 {
    TreeNode* traverse(TreeNode* root) {
        if(root == nullptr) return nullptr;
        TreeNode* r = root->right;
        root->right = traverse(root->left);
        root->left = nullptr;
        TreeNode* cur = root;
        while(cur->right != nullptr) {
            cur = cur->right;
        }
        cur->right = traverse(r);
        
        return root;
    }
public:
    void flatten(TreeNode* root) {
       traverse(root);
    }
};



class Solution_L1_copy {
public:
    // 定义：将以 root 为根的树拉平为链表
    void flatten(TreeNode* root) {
        // base case
        if (root == nullptr) return;

        // 利用定义，把左右子树拉平
        flatten(root->left);
        flatten(root->right);

        // *** 后序遍历位置 ***
        // 1、左右子树已经被拉平成一条链表
        TreeNode* left = root->left;
        TreeNode* right = root->right;

        // 2、将左子树作为右子树
        root->left = nullptr;
        root->right = left;

        // 3、将原先的右子树接到当前右子树的末端
        TreeNode* p = root;
        while (p->right != nullptr) {
            p = p->right;
        }
        p->right = right;
    }
};