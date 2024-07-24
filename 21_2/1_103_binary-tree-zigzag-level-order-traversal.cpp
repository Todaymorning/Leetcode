// https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal
// 103. 二叉树的锯齿形层序遍历
// 思路
// 中等
// 相关标签
// 相关企业
// 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

// 示例 1：
// 输入：root = [3,9,20,null,null,15,7]
// 输出：[[3],[20,9],[15,7]]

// 示例 2：
// 输入：root = [1]
// 输出：[[1]]

// 示例 3：
// 输入：root = []
// 输出：[]

// 提示：
// 树中节点数目在范围 [0, 2000] 内
// -100 <= Node.val <= 100


#include<iostream>
#include<queue>
#include<vector>
using std::vector;
using std::queue;
using std::deque;


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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

    }
};


// 2024年4月30日
// 16:12--16:25
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if(root == nullptr) return result;
        queue<TreeNode*> que;
        que.push(root);
        int size;
        bool flag = true;
        while (!que.empty()) {
            size = que.size();
            result.push_back(vector<int>(size));
            if(flag) {
                for(int i=0; i<size; i++) {
                    TreeNode* cur = que.front();
                    que.pop();
                    result.back()[i] = cur->val;
                    if(cur->left) que.push(cur->left);
                    if(cur->right) que.push(cur->right);
                }
            }
            else {
                for(int i=size-1; i>=0; i--) {
                    TreeNode* cur = que.front();
                    que.pop();
                    result.back()[i] = cur->val;
                    if(cur->left) que.push(cur->left);
                    if(cur->right) que.push(cur->right);
                }
            }
            flag = !flag;
        }
        return result;
    }
};



// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/solutions/530400/er-cha-shu-de-ju-chi-xing-ceng-xu-bian-l-qsun/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_G1_copy {
public:
    vector<vector<int>> zigzagLevelOrder (TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) {
            return ans;
        }

        queue<TreeNode*> nodeQueue;
        nodeQueue.push (root);
        bool isOrderLeft = true;

        while (!nodeQueue.empty ()) {
            deque<int> levelList;
            int size = nodeQueue.size ();
            for (int i = 0; i < size; ++i) {
                auto node = nodeQueue.front ();
                nodeQueue.pop ();
                if (isOrderLeft) {
                    levelList.push_back (node->val);
                } else {
                    levelList.push_front (node->val);
                }
                if (node->left) {
                    nodeQueue.push (node->left);
                }
                if (node->right) {
                    nodeQueue.push (node->right);
                }
            }
            ans.emplace_back (vector<int>{levelList.begin (), levelList.end ()});
            isOrderLeft = !isOrderLeft;
        }

        return ans;
    }
};