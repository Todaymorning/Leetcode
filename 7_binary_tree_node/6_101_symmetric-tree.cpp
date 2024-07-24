// 101. 对称二叉树
// 给你一个二叉树的根节点 root ， 检查它是否轴对称。

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



// 14:50——15:00——15:15——15:54
// 迭代法层序遍历时判断每一层是否对称
class Solution_M1 {
    bool levelOrder(TreeNode* root) {
        if(root == nullptr) return true;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        while(!q.empty()) {
            TreeNode* cur;
            int size = q.size();
            if(size % 2 != 0 && depth != 0) { // 除root外 某一层为单数时肯定不对称，因此返回 false
                return false;
            }
            vector<TreeNode*> vec(size, nullptr);   // 初始化为 nullptr，vec中存放节点地址
            for(int i=0; i<size; i++) {
                cur = q.front();
                q.pop();
                if(cur != nullptr) {                // 节点非空时才有存左右节点的必要
                    vec[i] = cur;
                    q.push(cur->left);              // 空的也需要存，因为这里可能影响对称性（null 3 3 null）和（null 3 null 3）
                    q.push(cur->right);
                }
            }
            for(int i=0; i<size/2; i++) {           // 判断该层的对称性
                if(vec[i] == nullptr || vec[size-1-i] == nullptr) {     // 有nullptr判断nullptr
                    if (vec[i] != vec[size-1-i]) return false;
                    else continue;
                }
                if(vec[i]->val != vec[size-1-i]->val) return false;     // 无nullptr判断val
            }
            depth++;
        }
        return true;
    }
public:
    bool isSymmetric(TreeNode* root) {
        bool result = levelOrder(root);
        return result;
    }
};




// 16:05——16:21
// 递归法层序遍历后判断是否对称
class Solution_M2 {
    void levelOrder(TreeNode* root, vector<vector<TreeNode*>>& level, int depth) {
        if(depth == int(level.size())) level.push_back(vector<TreeNode*>());
        level[depth].push_back(root);
        if(root == nullptr) return; // 挪动结束递归的条件，是为了将最后一层或第一层的nullptr加入level中
        levelOrder(root->left, level, depth + 1);
        levelOrder(root->right, level, depth + 1);
    }
public:
    bool isSymmetric(TreeNode* root) {
        vector<vector<TreeNode*>> level;
        levelOrder(root, level, 0);

        int m = level.size();
        for(int i=0; i<m; i++) {
            int n = level[i].size();
            if(n%2 != 0 && i != 0) {    // 个数是否满足对称
                return false;
            }
            for(int j=0; j<n/2; j++) {
                if(level[i][j] == nullptr || level[i][n-1-j] == nullptr) {
                    if(level[i][j] != level[i][n-1-j])
                        return false;
                    else 
                        continue;
                }
                if(level[i][j]->val != level[i][n-1-j]->val) return false;
            }
        }
        return true;
    }
};


// 16:29——16:48
// 递归法判断一个节点的两个子树是否对称
// 不使用遍历，将问题分解
 // 递归判断左右两侧节点是否相等
 
// 1.确定递归函数的参数和返回值
// 因为我们要比较的是根节点的两个子树是否是相互翻转的，进而判断这个树是不是对称树，所以要比较的是两个树，
// 参数自然也是左子树节点和右子树节点。
// 返回值自然是 bool 类型。
// bool compare(TreeNode* left, TreeNode* right)
// 2.确定终止条件
        // // 首先排除空节点的情况
        // if (left == NULL && right != NULL) return false;
        // else if (left != NULL && right == NULL) return false;
        // else if (left == NULL && right == NULL) return true;
        // // 排除了空节点，再排除数值不相同的情况
        // else if (left->val != right->val) return false;
// 3.确定单层递归逻辑

// 启发自 D1
class Solution_D1 {
    bool compare(TreeNode* left, TreeNode* right) {
        if(left == nullptr || right == nullptr) {   // 左右节点只要有一个是nullptr时不用继续递归了
            return left == right;
        }
        // 前序位置
        // 可以用 bool cur = left->val == right->val
        // 这样前中后序位置都可以放
        bool in = compare(left->left, right->right);    // 内侧左右节点判断
        // 中序位置
        bool out = compare(left->right, right->left);   // 外侧左右节点判断
        // 后序位置
        return in && out && left->val == right->val;
    }
public:
    bool isSymmetric(TreeNode* root) {
        bool result = compare(root->left, root->right);
        return result;
    }
};

// 终止递归的条件，这里可以使得递归结束更早
class Solution_D1_2 {
    bool compare(TreeNode* left, TreeNode* right) {
        if(left == nullptr || right == nullptr) {   // 左右节点只要有一个是nullptr时不用递归了
            return left == right;
        }
        else if (left->val != right->val) {         // 节点值不一样也不用递归了
            return false;
        }
        // 前序位置
        bool in = compare(left->left, right->right);    // 内侧左右节点判断
        // 中序位置
        bool out = compare(left->right, right->left);   // 外侧左右节点判断
        // 后序位置
        return in && out;
    }
public:
    bool isSymmetric(TreeNode* root) {
        bool result = compare(root->left, root->right);
        return result;
    }
};



// 迭代法——使用队列
class Solution_D2_1 {
    bool compare(TreeNode* root) {
        if(root == nullptr) return true;
        queue<TreeNode*> q;
        q.push(root->left); // 加入左右节点
        q.push(root->right);
        while(!q.empty()) {
            TreeNode* left = q.front(); // 获取左右节点
            q.pop();
            TreeNode* right = q.front();
            q.pop();
            if(left == nullptr || right == nullptr) {   // 比较左右节点
                if(left != right) return false;
            }
            else if(left->val != right->val) {
                return false;
            }
            if(left != nullptr && right != nullptr) {   // 添加左右节点，先外后内 / 先内后外
                q.push(left->left);
                q.push(right->right);
                q.push(left->right);
                q.push(right->left);
            }
        }
        return true;
    }
public:
    bool isSymmetric(TreeNode* root) {
        bool result = compare(root);
        return result;
    }

};


// 迭代法——使用栈
class Solution_D2_2 {
    bool compare(TreeNode* root) {
        if(root == nullptr) return true;
        stack<TreeNode*> stk;
        stk.push(root->left);   // 加入左右节点
        stk.push(root->right);
        while(!stk.empty()) {
            TreeNode* right = stk.top();    // 先进后出，弹出右左节点
            stk.pop();
            TreeNode* left = stk.top();
            stk.pop();
            if(left == nullptr || right == nullptr) {   // 比较左右节点
                if(left != right) return false;
            }
            else if(left->val != right->val) {
                return false;
            }
            if(left != nullptr && right != nullptr) {   // 添加左右节点
                stk.push(left->left);
                stk.push(right->right);
                stk.push(left->right);
                stk.push(right->left);
            }
        }
        return true;
    }
public:
    bool isSymmetric(TreeNode* root) {
        bool result = compare(root);
        return result;
    }
};

