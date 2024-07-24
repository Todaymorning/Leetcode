// 538. 把二叉搜索树转换为累加树
// 中等
// 给出二叉搜索树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），
// 使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

// 提示：
// 树中的节点数介于 0 和 10^4 之间。
// 每个节点的值介于 -10^4 和 10^4 之间。
// 树中的所有值互不相同。
// 给定的树为二叉搜索树。


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
    TreeNode* convertBST(TreeNode* root) {

    }
};


// 16:36--16:43
// 所有大于等于当前节点的值之和
// 反向中序遍历 + 记录前面节点的和
// 中序:左中右------反向：右中左
// 递归
class Solution_M1_D1 {
    int sum = 0;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        // 右
        traverse(root->right);
        // 中
        sum += root->val;
        root->val = sum;
        // 左
        traverse(root->left);
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        traverse(root);
        return root;
    }
};

// 16:47--16:52
// 栈迭代反向中序遍历
// 用 pre 与 sum 的思想上稍微差别，一个是上个节点，一个是外部工具
class Solution_M2_D2 {
    int pre = 0;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        stack<TreeNode*> s;
        TreeNode* cur = root;
        while(!s.empty() || cur != nullptr) {
            if(cur != nullptr) {
                s.push(cur);
                cur = cur->right;   //
            }
            else {
                cur = s.top();
                s.pop();
                cur->val += pre;
                pre = cur->val;
                cur = cur->left;    //
            }
        }
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        traverse(root);
        return root;
    }
};

// 16:55--17:02
// 比较统一的反向中序迭代
// 栈迭代反向中序遍历
// 中序：左中右，栈内：右中左，反向：左中右
class Solution {
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        stack<TreeNode*> s;
        s.push(root);
        TreeNode* cur;
        int pre = 0;
        while(!s.empty()) {
            cur = s.top();
            if(cur != nullptr) {
                s.pop();
                if(cur->left != nullptr) s.push(cur->left); //
                s.push(cur);
                s.push(nullptr);
                if(cur->right != nullptr) s.push(cur->right); //
            }
            else {
                s.pop();
                cur = s.top();
                cur->val += pre;    // 处理节点的顺序就是左中右，处理节点时再处理pre
                pre = cur->val;
                s.pop();
            }
        }
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        traverse(root);
        return root;
    }
};

