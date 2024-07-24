// Medium
// 617. 合并二叉树
// 给你两棵二叉树： root1 和 root2 。
// 想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。
//你需要将这两棵树合并成一棵新二叉树。合并的规则是：
// 如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，不为 null 的节点将直接作为新二叉树的节点。
// 返回合并后的二叉树。
// 注意: 合并过程必须从两个树的根节点开始。
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
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {

    }
};


// 16:40——17:11
class Solution_M1 {
    TreeNode* traverse(TreeNode* root1, TreeNode* root2) {
        // 两个都是空，直接返回
        if(root1 == nullptr && root2 == nullptr) return nullptr;
        TreeNode* root;
        // 两个都不为空
        if(root1 != nullptr && root2 != nullptr) {
            root = new TreeNode(root1->val + root2->val);
            root->left = traverse(root1->left, root2->left);
            root->right = traverse(root1->right, root2->right);
        }
        // 只有一个为空
        if(root1 == nullptr || root2 == nullptr) {
            if(root1 != nullptr) {
                root = new TreeNode(root1->val);
                root->left = traverse(root1->left, nullptr);
                root->right = traverse(root1->right, nullptr);
            }
            else {
                root = new TreeNode(root2->val);
                root->left = traverse(nullptr, root2->left);
                root->right = traverse(nullptr, root2->right);
            }
        }
        return root;
    }
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        return traverse(root1, root2);
    }
};


// 新建树，简化版
// D1的方法修改了 t1 的结构，当然也可以不修改 t1 和 t2 的结构，重新定义一个树。
// 不修改输入树的结构
class Solution_D2 {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == NULL) return t2;  // 这里其实也不对，上面的才是完全新建，这里还是运用了后面没有的子树
        if (t2 == NULL) return t1;
        // 重新定义新的节点，不修改原有两个树的结构 // 这里只是没有修改原有树的值
        TreeNode* root = new TreeNode(0);
        root->val = t1->val + t2->val;
        root->left = mergeTrees(t1->left, t2->left);
        root->right = mergeTrees(t1->right, t2->right);
        return root;
    }
};


// 前序遍历
// 简化
// 利用其中的一个树，但是这样就不能随便删除已存在的树了
// 递归时有一个为空，那么可以直接结束递归
class Solution_D1_1 {
    TreeNode* traverse(TreeNode* root1, TreeNode* root2) {
        if(root1 == nullptr) return root2;
        if(root2 == nullptr) return root1;
        root1->val += root2->val;
        root1->left = traverse(root1->left, root2->left);
        root1->right = traverse(root1->right, root2->right);
        return root1;
    }
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        return traverse(root1, root2);
    }
};


// 中序遍历，简化版
class Solution_D2_2 {
    TreeNode* traverse(TreeNode* t1, TreeNode* t2) {
        if(t1 == nullptr) return t2;
        if(t2 == nullptr) return t1;
        t1->left = traverse(t1->left, t2->left);
        t1->val += t2->val;
        t1->right = traverse(t1->right, t2->right);
        return t1;
    }
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        return traverse(root1, root2);
    }
};

// 中序遍历，简化版
class Solution_D1_3 {
    TreeNode* traverse(TreeNode* t1, TreeNode* t2) {
        if(t1 == nullptr) return t2;
        if(t2 == nullptr) return t1;
        t1->left = traverse(t1->left, t2->left);
        t1->right = traverse(t1->right, t2->right);
        t1->val += t2->val;
        return t1;
    }
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        return traverse(root1, root2);
    }
};



// 迭代法
// 运用判断树是否对称的队列层序遍历
// t1 t2 的left right
// 1  1：迭代
// 1  0：结束迭代
// 0  1：赋值给t1
// 0  0：结束迭代

class Solution_D3_copy {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr) return t2;
        if (t2 == nullptr) return t1;
        queue<TreeNode*> que;
        que.push(t1);
        que.push(t2);
        while(!que.empty()) {
            TreeNode* node1 = que.front(); que.pop();
            TreeNode* node2 = que.front(); que.pop();
            // 此时两个节点一定不为空，val相加
            node1->val += node2->val;

            // 如果两棵树左节点都不为空，加入队列
            if (node1->left != nullptr && node2->left != nullptr) {
                que.push(node1->left);
                que.push(node2->left);
            }
            // 如果两棵树右节点都不为空，加入队列
            if (node1->right != nullptr && node2->right != nullptr) {
                que.push(node1->right);
                que.push(node2->right);
            }

            // 下面的两个判断不用管t2为空的情况，这样就不用继续迭代了，直接继承 t1的节点
            // 当t1的左节点为空 t2左节点不为空，就赋值过去
            if (node1->left == nullptr && node2->left != nullptr) {
                node1->left = node2->left;
            }
            // 当t1的右节点为空 t2右节点不为空，就赋值过去
            if (node1->right == nullptr && node2->right != nullptr) {
                node1->right = node2->right;
            }
        }
        return t1;
    }
};