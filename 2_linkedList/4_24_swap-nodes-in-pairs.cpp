// 24. 两两交换链表中的节点
// https://leetcode.cn/problems/swap-nodes-in-pairs/
// 思路
// 中等
// 给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

// 示例 1：
// 输入：head = [1,2,3,4]
// 输出：[2,1,4,3]

// 示例 2：
// 输入：head = []
// 输出：[]

// 示例 3：
// 输入：head = [1]
// 输出：[1]
 

// 提示：
// 链表中节点的数目在范围 [0, 100] 内
// 0 <= Node.val <= 100

// 24. 两两交换链表中的节点
// 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
// 你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode * next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode * next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {

    }
};


ListNode * swpaPaires(ListNode * head)
{
    ListNode * dummyHead = new ListNode(0);
    dummyHead->next = head;
    ListNode * current = dummyHead;
    while(current->next != nullptr && current->next->next != nullptr)   // 有两个可以交换
    {
        ListNode * temp1 = current->next;   // 保存之前的链接关系
        ListNode * temp2 = current->next->next->next;
        current->next = current->next->next;    // 改变链接关系
        current->next->next = temp1;
        current->next->next->next = temp2;
        current = current->next->next;          // 当前节点后移两位
    }
    head = dummyHead->next;
    delete dummyHead;
    return head;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 15:30--15:33(读题找思路)--15:46--16:08(思路错误，相邻两个交换后第三个仍是3)
// 链表数目：0 1 2 多
// (1, p2)--(2, p3)--(3, p4)
#if 0
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // 0 1 个节点
        if(head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* result = head->next;
        while(head != nullptr && head->next != nullptr) {
            ListNode* temp = head->next;
            head->next = head->next->next;
            temp->next = head;
            head = head->next;
        }
        return result;
    }
};
#endif


// 设置一个虚拟头节点
class Solution_S2_D1_M1 {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* H = new ListNode();
        H->next = head;
        head = H;
        // head --> 1 --> 2 --> 3
        while(head->next != nullptr && head->next->next != nullptr) {
            ListNode* temp1 = head->next;               // 1
            ListNode* temp2 = head->next->next->next;   // 3
            head->next = head->next->next;
            head->next->next = temp1;
            temp1->next = temp2;
            head = head->next->next;
        }
        return H->next;
    }
};


// 在不好理清交换关系的时候，用空间换时间，使用更多的空间保存原始顺序
class Solution_S2_D1_M2 {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* H = new ListNode();
        H->next = head;
        head = H;
        // head --> 1 --> 2 --> 3
        while(head->next != nullptr && head->next->next != nullptr) {
            ListNode* temp1 = head->next;   // 1
            ListNode* temp2 = temp1->next;  // 2
            ListNode* temp3 = temp2->next;  // 3
            head->next = temp2;
            temp2->next = temp1;
            temp1->next = temp3;
            head = head->next->next;
        }
        return H->next;
    }
};




// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_S2_L1_copy {
    // 定义：输入以 head 开头的单链表，将这个单链表中的每两个元素翻转，
    // 返回翻转后的链表头结点
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { //递归结束条件
            return head;
        }
        ListNode* first = head;
        ListNode* second = head->next;
        ListNode* others = head->next->next;
        // 先把前两个元素翻转
        second->next = first;
        // 利用递归定义，将剩下的链表节点两两翻转，接到后面
        first->next = swapPairs(others);
        // 现在整个链表都成功翻转了，返回新的头结点
        return second;

    }
};
