// Easy
// 700. 二叉搜索树中的搜索
// 给定二叉搜索树（BST）的根节点 root 和一个整数值 val。
// 你需要在 BST 中找到节点值等于 val 的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 null 。

// 二叉搜索树是一个有序树：
// 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
// 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
// 它的左、右子树也分别为二叉搜索树

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
    TreeNode* searchBST(TreeNode* root, int val) {
        return nullptr;
    }
};

// 其他解法：
// 正常二叉树的遍历都可以试一下

// 递归
// 二叉搜索树左节点比终结点小，右节点比中节点大
class Solution_D1_M1 {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr) return nullptr;
        if(root->val == val) return root;
        TreeNode* result;
        if(root->val > val) result = searchBST(root->left, val);
        if(root->val < val) result = searchBST(root->right, val);
        return result;
    }
};


// 一提到二叉树遍历的迭代法，可能立刻想起使用栈来模拟深度遍历，使用队列来模拟广度遍历。
// 对于二叉搜索树可就不一样了，因为二叉搜索树的特殊性，也就是节点的有序性，可以不使用辅助栈或者队列就可以写出迭代法。
// 对于一般二叉树，递归过程中还有回溯的过程，例如走一个左方向的分支走到头了，那么要调头，在走右分支。
// 而对于二叉搜索树，不需要回溯的过程，因为节点的有序性就帮我们确定了搜索的方向。

class Solution_D2 {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == nullptr || root->val == val) return root;
        TreeNode* cur = root;
        while(cur != nullptr) {
            if(cur->val > val)  cur = cur->left;    // 大了往左走
            else if(cur->val < val) cur = cur->right;    // 小了往右走
            else return cur;
        }
    }
};
