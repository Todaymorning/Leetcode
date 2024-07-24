// 559. n叉树的最大深度
// 给定一个 n 叉树，找到其最大深度。
// 最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。

#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using std::stack;
using std::vector;
using std::queue;
struct Node {
    int val;
    vector<Node*> children;
    Node() : val(0) {}
    Node(int x) : val(x) {}
    Node(int x, vector<Node*> children) : val(x), children(children) {}
};


// 17:05——17:16
// 递归分解问题
// 动态规划
// 函数返回值，根据返回值在后序位置(离开一个节点的时候)处理
class Solution_L2 {
    int traverse(Node* root) {
        if(root == nullptr) return 0;
        int size = root->children.size();
        int depth = 0;
        for(int i=0; i<size; i++) {
            int child_depth = traverse(root->children[i]);
            depth =  child_depth > depth ? child_depth : depth;
        }
        return depth + 1;
    }
public:
    int maxDepth(Node* root) {
        int result = 0;
        result = traverse(root);
        return result;
    }
};


// 17:16——17:24
// 递归 深度回溯
// 改变一个全局变量
// 进入一个节点的时候做一些处理，退出该节点的时候恢复之前的状态——即回溯
class Solution_L1_D1 {
    void traverse(Node* root) {
        if(root == nullptr) return;
        cur_depth++;
        result = result > cur_depth ? result : cur_depth;
        int size = root->children.size();
        for(int i=0; i<size; i++) {
            traverse(root->children[i]);
        }
        cur_depth--;
    }
public:
    int result = 0;
    int cur_depth = 0;
    int maxDepth(Node* root) {
        traverse(root);
        return result;
    }
};



// 9:41——9:50
// 层序遍历
// 迭代遍历，用队列

class Solution_D2 {
    int traverse(Node* root) {
        if(root == nullptr) return 0;
        queue<Node*> q;
        q.push(root);
        Node* cur;
        int depth = 0;
        while(!q.empty()) {
            depth++;
            int size = q.size();
            for(int i=0; i<size; i++) {
                cur = q.front();
                q.pop();
                int children = cur->children.size();
                for(int j=0; j<children; j++) {
                    if(cur->children[j] != nullptr) q.push(cur->children[j]);
                }
            }
        }
        return depth;
    }
public:
    int maxDepth(Node* root) {
        int result = 0;
        result = traverse(root);
        return result;
    }
};
