// 206. 反转链表
// https://leetcode.cn/problems/reverse-linked-list/
// labuladong 题解
// 简单
// 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

// 示例 1：
// 输入：head = [1,2,3,4,5]
// 输出：[5,4,3,2,1]

// 示例 2：
// 输入：head = [1,2]
// 输出：[2,1]

// 示例 3：
// 输入：head = []
// 输出：[]

// 提示：
// 链表中节点的数目范围是 [0, 5000]
// -5000 <= Node.val <= 5000


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
    ListNode* reverseList(ListNode* head) {
        
    }
};


// 双指针法
// 时间复杂度: O (n)
// 空间复杂度: O (1)
ListNode * reverseList1(ListNode * head)
{
    ListNode * previous = nullptr;
    ListNode * current = head;
    ListNode * temp;
    while(current)
    {
        temp = current->next;   // 保存下一节点，因为下面要改变 current->next
        current->next = previous;   // 指向反转
        previous = current;     // previous 后移
        current = temp;         // current 后移
    }
    return previous;    // 循环结束后 current指向 nullptr，previous指向最后一个
}


// 递归
// 时间复杂度: O (n), 要递归处理链表的每个节点
// 空间复杂度: O (n), 递归调用了 n 层栈空间
ListNode * reverse(ListNode * previous, ListNode * current)
{
    if(current == nullptr)
        return previous;
    ListNode * temp = current->next;
    current->next = previous;
    // previous = current;
    // current = temp;
    return reverse(current, temp);
}
ListNode * reservList2(ListNode * head)
{
    // ListNode* cur = head;
    // ListNode* pre = NULL;
    return reverse(nullptr, head);  // 调用递归函数
}


// 从后往前递归
// 时间复杂度: O (n)
// 空间复杂度: O (n)
ListNode * reverseList3(ListNode * head)
{
    // 边缘条件判断
    if(head == nullptr)
        return nullptr;
    if(head->next == nullptr)
        return head;
    // 递归调用，翻转第二个节点开始往后的链表
    ListNode * last = reverseList3(head->next);
    // 翻转头节点与第二个节点的指向
    head->next->next = head;
    // 此时的head节点为尾节点,next需要指向nullptr
    head->next = nullptr;
    return last;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 10:40--10:55(不会)--11:01(看思路)--11:03
class Solution_S2_D1_M1 {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        ListNode* temp;
        while(cur != nullptr) {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre; // 循环结束后 current 指向 nullptr
    }
};

// 11:21--11:26
// 分开递归
class Solution_S2_D2_M2 {
    // 返回翻转后的头节点
    ListNode* reverse(ListNode* pre, ListNode* cur) {
        if(cur == nullptr) return pre;
        ListNode* temp = cur->next; // 暂存
        cur->next = pre;            // 反转
        // pre = cur, cur = temp;
        return reverse(cur, temp);  // 递归
    }
public:
    ListNode* reverseList(ListNode* head) {
        // cur = head, pre = nullptr
        return reverse(nullptr, head);
    }
};


// 11:28--
// 原地递归
// 从后往前递归
// ()-->()<--()<--()
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // 单个节点或递归到了最后一个节点，可以返回
        if(head == nullptr || head->next == nullptr)  return head;

        // 递归调用，翻转第二个节点开始往后的链表
        // 后面还有多个节点，保存返回的头节点，以供返回
        ListNode* last = reverseList(head->next);

        // 下面是递归中的处理：
        // 翻转头节点与第二个节点的指向
        head->next->next = head;
        // 此时的 head 节点为尾节点，next 需要指向 nullptr
        head->next = nullptr;                           // ***
        return last;
    }
};