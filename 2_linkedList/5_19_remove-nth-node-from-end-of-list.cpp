// 19. 删除链表的倒数第 N 个结点
// https://leetcode.cn/problems/remove-nth-node-from-end-of-list
// labuladong 题解
// 中等
// 提示
// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

// 示例 1：
// 输入：head = [1,2,3,4,5], n = 2
// 输出：[1,2,3,5]

// 示例 2：
// 输入：head = [1], n = 1
// 输出：[]

// 示例 3：
// 输入：head = [1,2], n = 1
// 输出：[1]

// 提示：
// 链表中结点的数目为 sz
// 1 <= sz <= 30
// 0 <= Node.val <= 100
// 1 <= n <= sz


// 19. 删除链表的倒数第 N 个节点
// 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
// 链表中结点的数目为 sz
// 1 <= sz <= 30
// 0 <= Node.val <= 100
// 1 <= n <= sz
// 思路：
// 双指针的经典应用，如果要删除倒数第 n 个节点，让 fast 移动 n 步，
// // 然后让 fast 和 slow 同时移动，直到 fast 指向链表末尾。删掉 slow 所指向的节点就可以了。

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {

    }
};




ListNode * removeNthFromEnd(ListNode * head, int n)
{
    ListNode * dummyHead = new ListNode(0);
    dummyHead->next = head;
    ListNode * fast = dummyHead;
    ListNode * slow = dummyHead;
    while(fast != nullptr && n--)
    {
        fast = fast->next;
    }
    fast = fast->next;  // fast和slow中间有n个，fast指向nullptr时需要删除 slow 的下一个
    while(fast != nullptr)
    {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode * temp = slow->next;
    slow->next = slow->next->next;
    delete temp;
    head = dummyHead->next;
    delete dummyHead;
    return head;
}



// 17:11--17:24
// 双指针，不加虚拟头节点
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* left = head;  // 指向被删除的前一个节点
        ListNode* right = head;
        while(n > 0 && right != nullptr) {
            right = right->next;
            n--;
        }
        // 删除 head
        if(n == 0 && right == nullptr) {
            // ListNode* temp = head->next;
            // delete head;
            return head->next;
        }
        while(right->next != nullptr) {
            left = left->next;
            right = right->next;
        }
        left->next = left->next->next;
        // ListNode* temp = left->next;
        // delete temp;
        return head;
    }
};


// 15:24--15:38
// 双指针，添加虚拟头节点
// 有虚拟头节点后就不用单独处理删除头节点的问题了
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // if(head == nullptr || head->next == nullptr) {   ***
        //     return head;
        // }
        ListNode* H = new ListNode();
        H->next = head;
        ListNode* fast = H;
        ListNode* slow = H;
        while(n > 0 && fast->next != nullptr) {
            fast = fast->next;
            n--;
        }
        while(fast->next != nullptr) {  // slow 指向被删除的前一个节点
            fast = fast->next;
            slow = slow->next;
        }
        // 正常程序需要 释放 虚拟头节点和被删除节点
        slow->next = slow->next->next;
        return H->next;
    }
};