// Easy
// 222. 完全二叉树的节点个数
// 给出一个完全二叉树，求出该树的节点个数。
// 示例 1：
// 输入：root = [1,2,3,4,5,6]
// 输出：6

// 示例 2：
// 输入：root = []
// 输出：0

// 示例 3：
// 输入：root = [1]
// 输出：1
// 提示：

// 树中节点的数目范围是 [0, 5 * 10^4]
// 0 <= Node.val <= 5 * 10^4
// 题目数据保证输入的树是 完全二叉树


#include<iostream>
#include<queue>
#include<vector>
#include<stack>
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
// class Solution {
// public:
//     int countNodes(TreeNode* root) {

//     }
// };



// 简化版代码
// 时间复杂度：O(n)
// 空间复杂度：O(log n)，算上了递归系统栈占用的空间
class Solution_D1_L1 {
public:
    int countNodes(TreeNode* root) {
        if(root == nullptr) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};


// 递归问题分解
// 动态规划
// 完整版代码
// 递归完全遍历
class Solution_D1 {
    int count(TreeNode* root) {
        if(root == nullptr) return 0;
        int left = count(root->left);
        int right = count(root->right);
        return left + right + 1;
    }
public:
    int countNodes(TreeNode* root) {
        return count(root);
    }
};


// 迭代 层序遍历
// 时间复杂度：O(n)
// 空间复杂度：O(log n)
class Solution_D2 {
    int count(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* cur;
        int result = 0;
        while(!q.empty()) {
            int size = q.size();
            result += size; // 统计该层节点个数
            for(int i=0; i<size; i++) {
                cur = q.front();
                q.pop();
                if(cur->left != nullptr) q.push(cur->left);
                if(cur->right != nullptr) q.push(cur->right);
            }
        }
        return result;
    }
public:
    int countNodes(TreeNode* root) {
        return count(root);
    }
};


// 完全二叉树和满二叉树
// 递归非完全遍历
// 时间复杂度：O (log n × log n)
// 空间复杂度：O (log n)
// 由于完全二叉树的性质，其子树一定有一棵是满的，所以一定会触发 hl == hr，只消耗 O (logN) 的复杂度而不会继续递归。
// 算法的递归深度就是树的高度 O(logN)，每次递归所花费的时间就是 while 循环，需要 O (logN)，
// 所以总体的时间复杂度是 O(logN*logN)。
class Solution_D3_L2_1 {
    int count(TreeNode* root) {
        if(root == nullptr) return 0;
        TreeNode* left = root->left;
        TreeNode* right = root->right;
        int leftDepth = 0, rightDepth = 0;
        while(left != nullptr) {    // 左侧深度
            leftDepth++;
            left = left->left;
        }
        while(right != nullptr) {   // 右侧深度
            rightDepth++;
            right = right->right;
        }
        if(leftDepth == rightDepth) {       // 左右深度相等，满二叉树，不用继续迭代了
            return (2 << leftDepth) - 1;    // 2 << 1 = 2*2^1 = 2^(n+1)
        }
        return count(root->left) + count(root->right) + 1;
    }
public:
    int countNodes(TreeNode* root) {
        return count(root);
    }
};
// 和上面等价
class Solution_D3_L2_2 {
    int count(TreeNode* root) {
        // if(root == nullptr) return 0;
        // TreeNode* left = root->left;
        // TreeNode* right = root->right;
        TreeNode* left = root;  // 没有了上面的判断，需要在下面的判断加上去
        TreeNode* right = root;

        int leftDepth = 0, rightDepth = 0;
        while(left != nullptr) {
            leftDepth++;
            left = left->left;
        }
        while(right != nullptr) {
            rightDepth++;
            right = right->right;
        }
        if(leftDepth == rightDepth) {
            return (1 << leftDepth) - 1;    // 这里的 2 改为了 1 
        }
        return count(root->left) + count(root->right) + 1;
    }
public:
    int countNodes(TreeNode* root) {
        return count(root);
    }
};






