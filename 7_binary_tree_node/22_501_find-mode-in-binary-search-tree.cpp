// 501. 二叉搜索树中的众数
// 简单
// 给你一个含重复值的二叉搜索树（BST）的根节点 root ，找出并返回 BST 中的所有 众数（即，出现频率最高的元素）。
// 如果树中有不止一个众数，可以按 任意顺序 返回。

// 假定 BST 满足如下定义：
// 结点左子树中所含节点的值 小于等于 当前节点的值
// 结点右子树中所含节点的值 大于等于 当前节点的值
// 左子树和右子树都是二叉搜索树

// 提示：
// 树中节点的数目在范围 [1, 10^4] 内
// -10^5 <= Node.val <= 10^5

// 进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）


#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<unordered_map>
#include<algorithm> // min() max() sort()
using std::min;
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
    vector<int> findMode(TreeNode* root) {

    }
};


// 可能的解法：
// 递归中序遍历转化为有序数组，然后统计
// 递归中序遍历，遍历时统计
// 迭代中序遍历
// 统一的迭代中序遍历（可继续尝试）




// 15:50--16:11--16--22
// 递归中序遍历，全局变量保存前一个节点，当前数的个数和个数最大值
class Solution_M1_D2 {
    TreeNode* pre = nullptr;
    int cur_num = 1;
    int max_num = 1;
    vector<int> result;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        traverse(root->left);
        if(pre != nullptr) {
            if(root->val == pre->val) {
                cur_num++;
            }
            else {
                cur_num = 1;
            }
            if(cur_num == max_num) {    // 当前数的个数和最多的一样多
                // result为空或还没添加的时候，添加
                if(result.empty() || result.back() != root->val) {
                    result.push_back(root->val);
                }
            }
            if(cur_num > max_num) {     // 当前数的个数最多，前面肯定已经添加过了
                max_num = cur_num;      // 漏了     ***
                result.clear();
                result.push_back(root->val);
            }
        }
        else {  // 漏了只有一个根节点的情况 ***
            result.push_back(root->val);    // 根节点   ***
        }
        pre = root; // 更换pre
        traverse(root->right);
    }
public:
    vector<int> findMode(TreeNode* root) {
        traverse(root);
        return result;
    }
};


// 17:01--17：14
// 递归中序遍历，统计数量和判断是否是众数(添加)分开
class Solution_D2 {
    vector<int> result;
    TreeNode* pre;
    int maxCount = 0;
    int count = 0;
    void traverse(TreeNode* root) {
        if(root == nullptr) return;
        traverse(root->left);
        // 统计当前数量
        if(pre != nullptr) {
            if(root->val == pre->val) { // 与前一个节点值相同
                count++;
            }
            else {
                count = 1;  // 遇到新的值
            }
        }
        else {  // 第一个节点的时候
            count = 1;
        }

        // 当前数量与最大数量比较
        if(count == maxCount) {
            result.push_back(root->val);    // 相等时添加
        }
        else if(count > maxCount) {         // 更大时清空后添加
            maxCount = count;   // 更新最大个数
            result.clear();
            result.push_back(root->val);
        }

        pre = root;     // 更新前一个节点

        traverse(root->right);
    }
public:
    vector<int> findMode(TreeNode* root) {
        result.clear();
        traverse(root);
        return result;
    }
};




// 普通二叉树的众数
// 如果不是二叉搜索树，可以递归遍历，用map统计每个数的个数
// 启发自D1
class Solution_D1_copy {
    void traverse(TreeNode* root, unordered_map<int, int>& map) {
        if(root == nullptr) return;
        map[root->val]++;   // 统计元素频率，前中后序位置都可以
        traverse(root->left, map);
        traverse(root->right, map);
    }
    bool static cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // 降序
    }
public:
    vector<int> findMode(TreeNode* root) {
        vector<int> result;
        result.clear();
        if(root == nullptr) return result;
        unordered_map<int, int> map;
        // 遍历
        traverse(root, map);
        // 排序
        vector<pair<int, int>> vec(map.begin(), map.end()); // map转化为 vector
        sort(vec.begin(), vec.end(), cmp);  // 频率降序
        result.push_back(vec[0].first);
        int size = vec.size();
        for(int i=1; i<size; i++) {
            if(vec[i].second == vec[0].second)  // 频率相等，多个众数
                result.push_back(vec[i].first);
            else
                break;
        }
        return result;
    }
};


// 18:48
// 栈迭代中序遍历时处理
// 非统一的迭代
// 中序：左中右
class Solution_D3 {
    vector<int> traverse(TreeNode* root) {
        vector<int> result;
        if (root == nullptr) return result;
        stack<TreeNode*> s;
        TreeNode* pre = nullptr;
        int count = 0;
        int maxCount = 0;
        while(root!= nullptr || !s.empty()) {
            if(root != nullptr) {
                s.push(root);
                root = root->left;
            }
            else {
                root = s.top();
                s.pop();
                // 计数
                if(pre != nullptr) {
                    if(root->val == pre->val) {
                        count++;    // 老数字
                    }
                    else {
                        count = 1;  // 新数字
                    }
                }
                else {
                    count = 1;  // 根节点
                }
                // 根据大小更新result
                if(count == maxCount) {
                    result.push_back(root->val);
                }
                else if(count > maxCount) {
                    maxCount = count;
                    result.clear();
                    result.push_back(root->val);
                }
                pre = root;
                root = root->right;
            }
        }
        return result;
    }
public:
    vector<int> findMode(TreeNode* root) {
        return traverse(root);
    }
};







