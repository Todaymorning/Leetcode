// https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/description/
// 236. 二叉树的最近公共祖先
// labuladong 题解
// 思路
// 给定一个二叉树，找到该树中两个指定节点的最近公共祖先。
// 中等

// 提示
// 树中节点数目在范围 [2, 10^5] 内。
// -10^9 <= Node.val <= 10^9
// 所有 Node.val 互不相同 。
// p != q
// p 和 q 均存在于给定的二叉树中。


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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return nullptr;
    }
};

// 20：38--20：43 没思路
// 8：56--9:06
// 求最小公共祖先，需要从底向上遍历，那么二叉树，只能通过后序遍历（即：回溯）实现从底向上的遍历方式。
// 在回溯的过程中，必然要遍历整棵二叉树，即使已经找到结果了，依然要把其他节点遍历完，
// 因为要使用递归函数的返回值（也就是代码中的 left 和 right）做逻辑判断。
class Solution_L1_D1 {
    TreeNode* find(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        // root为其中一个节点，另一个不在以root为根节点的树中；—— return就不用再往后找了
        // root为其中一个节点，另一个在以root为根节点的树中；—— return不再往后找也可以，因为已经找到答案了
        if(root == p || root == q) {
            return root;     // root为其中一个节点，q p有一个为根节点
        }
        TreeNode* left = find(root->left, p, q);    // root左子树
        TreeNode* right = find(root->right, p, q);  // root右子树
        if(left != nullptr && right != nullptr) {   // root左右子树同时包含 p q，直接返回
            return root;
        }
        return left != nullptr ? left : right;      // 子树中只找到一个或没找到
        
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return find(root, p, q);
    }
};




//********************************************************************************************************************************
// 力扣第 1676 题「二叉树的最近公共祖先 IV」
// 依然给你输入一棵不含重复值的二叉树，但这次不是给你输入 p 和 q 两个节点了
// 而是给你输入一个包含若干节点的列表 nodes（这些节点都存在于二叉树中），让你算这些节点的最近公共祖先。
// 
// template < class Key,            //容器中存储元素的类型
//            class Hash = hash<Key>,    //确定元素存储位置所用的哈希函数
//            class Pred = equal_to<Key>,   //判断各个元素是否相等所用的函数
//            class Alloc = allocator<Key>   //指定分配器对象的类型
//            > class unordered_set;
// 默认哈希函数 hash<Key> 只适用于基本数据类型（包括 string 类型），而不适用于自定义的结构体或者类。
// unordered_set<int> values;
// for(TreeNode* node:nodes) {
//     values.insert(node->val);
// }
// if(values.count(root->val)) {
//     return root;
// }

class Solution_L1_1676 {
    TreeNode* find(TreeNode* root, vector<TreeNode*>& nodes) {
        if(root == nullptr) return root;
        // 前序位置
        int size = nodes.size();
        for(int i=0; i<size; i++) { // 判断 root在不在nodes中，也可以用 unordered_set
            if(root == nodes[i]) return root;   // 这里直接return，root为根节点的树中是否有其他nodes中的元素都没关系
        }
        TreeNode* left = find(root->left, nodes);
        TreeNode* right = find(root->right, nodes);
        // 后序位置，已经知道左右子树是否存在目标值
        if(left != nullptr && right != nullptr) {
            return root;
        }
        return left != nullptr ? left : right;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> nodes) {
        return find(root, nodes);
    }
};



//********************************************************************************************************************************
// 力扣第 1644 题「二叉树的最近公共祖先 II」：
// 给你输入一棵不含重复值的二叉树的，以及两个节点 p 和 q，如果 p 或 q 不存在于树中，则返回空指针，
// 否则的话返回 p 和 q 的最近公共祖先节点。

// p q 都有可能不在二叉树中
// 对二叉树进行完整遍历，不要找到一个就开始返回

// 10：28--10:36 写错
#if 0
class Solution_L1_1644 {
    TreeNode* find(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return root; // return nullptr;
        // 不在前序位置返回了，因为要完整遍历，需要在后序位置返回
        TreeNode* left = find(root->left, p, q);
        TreeNode* right = find(root->right, p, q);
        if(left != nullptr && right != nullptr) {
            return root;
        }
        return left != nullptr ? left : right;  // 有可能都是这句运行（只找到一个）
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return find(root, p, q);
    }
};
#endif

class Solution_L1_1644 {
    // 添加全局变量，记录节点是否在树中
    bool foundP = false;
    bool foundQ = false;
    TreeNode* find(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return root; // return nullptr;
        // 不在前序位置返回了，因为要完整遍历，需要在后序位置返回
        TreeNode* left = find(root->left, p, q);
        TreeNode* right = find(root->right, p, q);

        // 后序位置，判断当前节点是否是LCA
        if(left != nullptr && right != nullptr) {
            return root;
        }
        // 后序位置，判断当前节点是否是目标值
        if(root->val == p->val || root->val == q->val) {
            if(root->val == p->val) foundP = true;
            if(root->val == q->val) foundQ = true;
            return root;    // 只要找到一个目标值就可以有返回值，同时记录哪个节点在树中，方便判断是否返回nullptr
        }
        return left != nullptr ? left : right;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* result = find(root, p, q);
        if(!foundP || !foundQ) return nullptr;  // 迭代之外判断
        return result;
    }
};



//********************************************************************************************************************************
// 依然给你输入一棵不含重复值的二叉树，但这次不是给你输入 p 和 q 两个节点了
// 而是给你输入一个包含若干节点的列表 nodes（这些节点可能不存在于二叉树中），让你算这些节点的最近公共祖先。
class Solution_L1_M1 {
    TreeNode* find(TreeNode* root, vector<TreeNode*>& nodes, vector<int>& founds) {
        if(root == nullptr) return root;
        // 判断当前节点是否是目标值
        bool cur = false;
        for(int i=0; i<int(nodes.size()); i++) {
            if(root->val == nodes[i]->val) {
                founds[i] = 1;    // 找到时标记
                cur = true; // 记录当前节点是nodes中的
                break;
            }
        }
        TreeNode* left = find(root->left, nodes, founds);
        TreeNode* right = find(root->right, nodes, founds);
        // 后序位置
        if((left != nullptr && right != nullptr) || cur) {
            return root;
        }
        return left != nullptr ? left : right;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*>nodes) {
        int size = nodes.size();
        vector<int> founds(size, 0);    // 不要用 vector<bool>
        TreeNode* result = find(root, nodes, founds);
        int sum = 0;
        for(auto i:founds) sum += i;    // 计数，是否被全部找到
        if(sum != size) return nullptr;
        return result;
    }
};
// 验证
#if 0
class Solution_L1_M1_2 {
    TreeNode* find(TreeNode*root, vector<int>& nodes, vector<int>& founds) {
        if(root == nullptr) return root;
        // 判断当前节点是否是目标值
        bool cur = false;
        for(int i=0; i<int(nodes.size()); i++) {
            if(root->val == nodes[i]) {
                founds[i] = 1;    // 找到时标记
                cur = true; // 记录当前节点是nodes中的
                break;
            }
        }
        TreeNode* left = find(root->left, nodes, founds);
        TreeNode* right = find(root->right, nodes, founds);
        // 后序位置
        if(left != nullptr && right != nullptr) {
            return root;
        }
        if(cur) return root;
        return left != nullptr ? left : right;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<int>nodes) {
        int size = nodes.size();
        vector<int> founds(size, 0);    // 不要用 vector<bool>
        TreeNode* result = find(root, nodes, founds);
        int sum = 0;
        for(auto i:founds) sum += i;    // 计数，是否被全部找到
        if(sum != size) return nullptr;
        return result;
    }
};

// 层序遍历，由数组生成二叉树
void build(TreeNode* root, vector<int>& all) {
    queue<TreeNode*> q;
    root->val = all[0];
    q.push(root);
    TreeNode* cur;
    for(int i=1; i<int(all.size()); i+=2) {
        cur = q.front();
        q.pop();
        cur->left = new TreeNode(all[i]);
        cur->right = new TreeNode(all[i+1]);
        q.push(cur->left);
        q.push(cur->right);
    }
}

int main() {
    TreeNode* root;
    vector<int> all = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, NULL, NULL, 11, 12, 13};
    root = new TreeNode(0);
    build(root, all);
    Solution_L1_M1_2 s;
    vector<int> nodes = {8, 9, 10, 12, 4, 6, 7};
    TreeNode* result = s.lowestCommonAncestor(root, nodes);
    if(result!= nullptr) {
        std::cout << result->val;
    }
    else std::cout << "ok";
    return 0;
}

#endif




// 2024年4月30日
// 11:22--11:35(不会，看思路)
// 后续遍历
// 给定的条件： p q 都在二叉树中
class Solution {
    vector<TreeNode*> pH;
    vector<TreeNode*> qH;
    TreeNode* traveral(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        // 找到其中一个节点，不用往下找了，结果要不然就是root，要不然在root的上面
        if(root == p || root == q) return root;
        TreeNode* left = traveral(root->left, p, q);
        TreeNode* right = traveral(root->right, p, q);
        if(left && right) return root;  // p q 分别在 root 的两边，结果就是root
        return left == nullptr ? right : left;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return traveral(root, p, q);
    }
};