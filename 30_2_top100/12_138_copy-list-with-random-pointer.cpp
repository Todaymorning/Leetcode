// https://leetcode.cn/problems/copy-list-with-random-pointer/
// 138. 随机链表的复制
// 已解答
// 中等
// 相关标签
// 相关企业
// 提示
// 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

// 构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

// 例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

// 返回复制链表的头节点。

// 用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

// val：一个表示 Node.val 的整数。
// random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
// 你的代码 只 接受原链表的头节点 head 作为传入参数。

 

// 示例 1：



// 输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
// 输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
// 示例 2：



// 输入：head = [[1,1],[2,1]]
// 输出：[[1,1],[2,1]]
// 示例 3：



// 输入：head = [[3,null],[3,0],[3,null]]
// 输出：[[3,null],[3,0],[3,null]]
 

// 提示：

// 0 <= n <= 1000
// -104 <= Node.val <= 104
// Node.random 为 null 或指向链表中的节点。



#include<iostream>
#include<unordered_map>
#include<unordered_set>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        
    }
};




class Solution_L1_M1 {
public:
    Node* copyRandomList(Node* head) {
        // 15:25
        if(head == nullptr) return head;
        Node* newHead = new Node(head->val);
        Node* oldCur = head;
        Node* newCur = newHead;
        unordered_map<Node*, Node*> mp;
        mp[oldCur] = newCur;
        // mp[nullptr] = nullptr;
        while(oldCur->next != nullptr) {
            newCur->next = new Node(oldCur->next->val);
            mp[oldCur->next] = newCur->next;
            oldCur = oldCur->next;
            newCur = newCur->next;
        }
        newCur = newHead;
        oldCur = head;
        while(oldCur != nullptr) {
            // if(oldCur->random != nullptr)
            newCur->random = mp[oldCur->random];
            newCur = newCur->next;
            oldCur = oldCur->next;
        }
        return newHead;
    }
};






class Solution_L1_copy {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> originToClone;
        // 第一次遍历，先把所有节点克隆出来
        for (Node* p = head; p != nullptr; p = p->next) {
            if (originToClone.find(p) == originToClone.end()) {
                originToClone[p] = new Node(p->val);
            }
        }
        // 第二次遍历，把克隆节点的结构连接好
        for (Node* p = head; p != nullptr; p = p->next) {
            if (p->next != nullptr) {
                originToClone[p]->next = originToClone[p->next];
            }
            if (p->random != nullptr) {
                originToClone[p]->random = originToClone[p->random];
            }
        }
        // 返回克隆之后的头结点
        return originToClone[head];
    }
};

// 用递归的方式进行遍历
class Solution_L2_copy {
public:
    Node* copyRandomList(Node* head) {
        traverse(head);
        return originToClone[head];
    }

private:
    // 记录 DFS 遍历过的节点，防止走回头路
    unordered_set<Node*> visited;
    // 记录原节点到克隆节点的映射
    unordered_map<Node*, Node*> originToClone;

    // DFS 图遍历框架
    void traverse(Node* node) {
        if (node == nullptr) {
            return;
        }
        if (visited.find(node) != visited.end()) {
            return;
        }
        // 前序位置，标记为已访问
        visited.insert(node);
        // 前序位置，克隆节点
        if (originToClone.find(node) == originToClone.end()) {
            originToClone[node] = new Node(node->val);
        }
        Node* cloneNode = originToClone[node];

        // 递归遍历邻居节点，并构建克隆图
        // 递归之后，邻居节点一定存在 originToClone 中

        traverse(node->next);
        cloneNode->next = originToClone[node->next];

        traverse(node->random);
        cloneNode->random = originToClone[node->random];
    }
};