// 203. 移除链表元素
// https://leetcode.cn/problems/remove-linked-list-elements/
// 简单
// 给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。

// 示例 1：
// 输入：head = [1,2,6,3,4,5,6], val = 6
// 输出：[1,2,3,4,5]

// 示例 2：
// 输入：head = [], val = 1
// 输出：[]

// 示例 3：
// 输入：head = [7,7,7,7], val = 7
// 输出：[]

// 提示：
// 列表中的节点数目在范围 [0, 10^4] 内
// 1 <= Node.val <= 50
// 0 <= val <= 50

// 链表和数组的对比
// 链表：数据量不固定，频繁增删，较少查询
// 数组：数据量固定，较少增删，频繁查询

# include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode * next;
    ListNode() : val(0), next(nullptr)  {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode * next) : val(x), next(next)   {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {

    }
};




// 直接使用原来的链表来进行移除节点操作
ListNode * removeElements(ListNode * head, int val)
{
    // 删除头节点
    while(head != nullptr && head->val == val)
    {
        ListNode * temp = head; // 留待释放
        head = head->next;
        delete temp;
    }

    // 删除非头节点
    ListNode * current = head;
    while(current != nullptr && current->next != nullptr)   // 此时head不需要删除，后面还有节点
    {
        if(current->next->val == val)
        {
            ListNode * temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else
            current = current->next;
    }

    return head;
}


// 设置虚拟头节点进行操作
ListNode * removeElements2(ListNode * head, int val)
{
    ListNode * temphead = new ListNode(0);  // 虚拟头节点
    temphead->next = head;
    ListNode * current = temphead;
    while(current->next != nullptr)
    {
        if(current->next->val == val)
        {
            ListNode * temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else
            current = current->next;
    }
    head = temphead->next;
    return head;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 19:25--19:31(不会，看了上面代码)
// 增加虚拟头节点
class Solution_S2_D2_M1 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* H = new ListNode(0);  // 虚拟头节点
        H->next = head;
        ListNode* cur = H;
        while(cur->next != nullptr) {
            if(cur->next->val == val) {     // 删除节点，cur->next 指向下一个
                ListNode* temp = cur->next;
                cur->next = cur->next->next;// ***
                delete temp;
            }
            else {                          // ***
                cur = cur->next;            // cur 变成下一个
            }
        }
        return H->next;
    }
};

// ~--19:49--19:55(改错)
// 处理原有头节点
class Solution_S2_M2_D1 {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // 头节点需要删除
        while(head != nullptr && head->val == val) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
        ListNode* cur = head;
        // 中间节点需要删除
        while(cur != nullptr && cur->next != nullptr) {     // *** 后面还有节点才有可能需要接着删
            if(cur->next->val == val) {
                ListNode* temp = cur->next;                 // *** cur->next
                cur->next = cur->next->next;
                delete temp;
            }
            else {
                cur = cur->next;
            }
        }
        return head;
    }
};