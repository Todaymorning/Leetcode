// 337. 打家劫舍 III
// labuladong 题解思路
// 中等
// 小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。
// 除了 root 之外，每栋房子有且只有一个 “父 “房子与之相连。一番侦察之后，聪明的小偷意识到 “这个地方的所有房屋的排列类似于一棵二叉树”。
// 如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。
// 给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。

// 示例 1:
// 输入: root = [3,2,3,null,3,null,1]
// 输出: 7 
// 解释: 小偷一晚能够盗取的最高金额 3 + 3 + 1 = 7

// 示例 2:
// 输入: root = [3,4,5,1,3,null,1]
// 输出: 9
// 解释: 小偷一晚能够盗取的最高金额 4 + 5 = 9

// 提示：
// 树的节点数在 [1, 10^4] 范围内
// 0 <= Node.val <= 10^4



#include<iostream>
#include<unordered_map>
#include<sstream>
#include<string>
#include<vector>
using std::vector;
using std::string;
using std::pair;
using std::unordered_map;
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
    int rob(TreeNode* root) {

    }
};


// 11:36--11:44(读题找思路，看回溯行不行)--少了 root->val,且没有memo
// 不带 memo 超时
class Solution_M1 {
    int backtracking(TreeNode* root, int used) {
        if(root == nullptr) return 0;
        if(used == 1) {
            return root->val + backtracking(root->left, 0) + backtracking(root->right, 0);
        }
        else {
            int left = std::max(backtracking(root->left, 0), backtracking(root->left, 1));
            int right = std::max(backtracking(root->right, 0), backtracking(root->right, 1));
            return left + right;
        }
    }
public:
    int rob(TreeNode* root) {
        return std::max(backtracking(root, 1), backtracking(root, 0));
    }
};

// 10:37--11:07(加上 memo)
// 先使用 unordered<pair<TreeNode*,int>,int>，但是没有 对应的 hash 函数，因此改为 unordered<string,int>
// 带 memo 正常
class Solution_M2 {
    unordered_map<string, int> memo;
    int backtracking(TreeNode* root, int used) {
        if(root == nullptr) return 0;
        int result = 0;
        if(used == 1) {
            std::stringstream temp;
            temp << root << 1;
            if(memo.find(temp.str()) == memo.end()) {
                result = root->val + backtracking(root->left, 0) + backtracking(root->right, 0);
                memo[temp.str()] = result;
            }
            return memo[temp.str()];
        }
        else {
            std::stringstream temp;
            temp << root << 0;
            if(memo.find(temp.str()) == memo.end()) {
                int left = std::max(backtracking(root->left, 0), backtracking(root->left, 1));
                int right = std::max(backtracking(root->right, 0), backtracking(root->right, 1));
                result =  left + right;
                memo[temp.str()] = result;
            }
            return memo[temp.str()];
        }
    }
public:
    int rob(TreeNode* root) {
        return std::max(backtracking(root, 1), backtracking(root, 0));
    }
};



class Solution_L1_M3 {
    unordered_map<TreeNode*, int> memo;
    int dp(TreeNode* root) {
        if(root == nullptr) return 0;
        if(memo.count(root)) return memo[root];
        int do_it = root->val
                    + (root->left == nullptr ?
                    0 : dp(root->left->left) + dp(root->left->right))
                    + (root->right == nullptr ?
                    0 : dp(root->right->left) + dp(root->right->right));
        int not_do = dp(root->left) + dp(root->right);
        int res = std::max(do_it, not_do);
        memo[root] = res;
        return res;
    }
public:
    int rob(TreeNode* root) {
        return dp(root);
    }
};


// 暴力递归
// 时间复杂度：O (n^2)，这个时间复杂度不太标准，也不容易准确化，例如越往下的节点重复计算次数就越多
// 空间复杂度：O (log n)，算上递推系统栈的空间
class Solution_D1_copy {
public:
    int rob(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return root->val;
        // 偷父节点
        int val1 = root->val;
        if (root->left) val1 += rob(root->left->left) + rob(root->left->right); // 跳过root->left，相当于不考虑左孩子了
        if (root->right) val1 += rob(root->right->left) + rob(root->right->right); // 跳过root->right，相当于不考虑右孩子了
        // 不偷父节点
        int val2 = rob(root->left) + rob(root->right); // 考虑root的左右孩子
        return std::max(val1, val2);
    }
};

// 记忆化递归
// 时间复杂度：O (n)
// 空间复杂度：O (log n)，算上递推系统栈的空间
class Solution {
public:
    unordered_map<TreeNode* , int> umap; // 记录计算过的结果
    int rob(TreeNode* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return root->val;
        if (umap[root]) return umap[root]; // 如果umap里已经有记录则直接返回
        // 偷父节点
        int val1 = root->val;
        if (root->left) val1 += rob(root->left->left) + rob(root->left->right); // 跳过root->left
        if (root->right) val1 += rob(root->right->left) + rob(root->right->right); // 跳过root->right
        // 不偷父节点
        int val2 = rob(root->left) + rob(root->right); // 考虑root的左右孩子
        umap[root] = std::max(val1, val2); // umap记录一下结果
        return std::max(val1, val2);
    }
};



// 11:38--11:51
// 看过 D3 的思路后尝试
// 树形 dp 的入门题目，在树上进行状态转移
// 所以 dp 数组（dp table）以及下标的含义：下标为 0 记录不偷该节点所得到的的最大金钱，下标为 1 记录偷该节点所得到的的最大金钱。
// 所以本题 dp 数组就是一个长度为 2 的数组！
// 长度为 2 的数组怎么标记树中每个节点的状态呢？ 在递归的过程中，系统栈会保存每一层递归的参数。
// 时间复杂度：O (n)，每个节点只遍历了一次
// 空间复杂度：O (log n)，算上递推系统栈的空间
class Solution {
    vector<int> robTree(TreeNode* root) {
        if(root == nullptr) return vector<int>(2, 0);
        vector<int> left = robTree(root->left);
        vector<int> right = robTree(root->right);
        // 后序位置
        vector<int> res(2, 0);
        // 不偷父节点：此时偷不偷左右子节点都可以，找到最大值即可
        res[0] = std::max(left[0], left[1]) + std::max(right[0], right[1]);
        // 偷父节点：左右子节点都不能偷
        res[1] = root->val + left[0] + right[0];
        return res;
    }
public:
    int rob(TreeNode* root) {
        vector<int> result = robTree(root);
        return std::max(result[0], result[1]);
    }
};