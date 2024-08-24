// https://leetcode.cn/problems/palindrome-linked-list/description/?envType=study-plan-v2&envId=top-100-liked
// 234. 回文链表
// 已解答
// 简单
// 相关标签
// 相关企业
// 给你一个单链表的头节点 head ，请你判断该链表是否为
// 回文链表
// 。如果是，返回 true ；否则，返回 false 。

 

// 示例 1：


// 输入：head = [1,2,2,1]
// 输出：true
// 示例 2：


// 输入：head = [1,2]
// 输出：false
 

// 提示：

// 链表中节点数目在范围[1, 105] 内
// 0 <= Node.val <= 9
 

// 进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

#include<iostream>
#include<queue>
#include<vector>
using std::vector;
using std::queue;
using std::deque;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// 20:32--20:44
// 快慢指针，fast，slow，找到链表的中间节点
// 1 2 3 4 n
// 1 2 3 n
class Solution {
    ListNode* reverse(ListNode* head) {
        ListNode* pre = nullptr, * cur = head, * temp;
        while(cur != nullptr) {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre; // 返回新的头节点
    }
public:
    bool isPalindrome(ListNode* head) {
        // 找到链表中间节点 slow
        // 偶数个节点：fast没到 nullptr，slow 中间靠左
        // 奇数个节点：fast到了 nullptr，slow 中间
        ListNode* slow = head, * fast = head;
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        if(fast != nullptr) slow = slow->next;
        ListNode* left = head;
        ListNode* right = reverse(slow);
        while(right != nullptr) {   // 左右两个链表还没断开，只能用right判断
            if(left->val != right->val) return false;
            left = left->next;
            right = right->next;
        }
        return true;
    }
};
