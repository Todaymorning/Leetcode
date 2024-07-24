// 142. 环形链表 II
// https://leetcode.cn/problems/linked-list-cycle-ii/
// labuladong 题解
// 中等
// 给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
// 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，
// 评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
// 不允许修改 链表。

// 示例 1：
// 输入：head = [3,2,0,-4], pos = 1
// 输出：返回索引为 1 的链表节点
// 解释：链表中有一个环，其尾部连接到第二个节点。

// 示例 2：
// 输入：head = [1,2], pos = 0
// 输出：返回索引为 0 的链表节点
// 解释：链表中有一个环，其尾部连接到第一个节点。

// 示例 3：
// 输入：head = [1], pos = -1
// 输出：返回 null
// 解释：链表中没有环。

// 提示：
// 链表中节点的数目范围在范围 [0, 10^4] 内
// -10^5 <= Node.val <= 10^5
// pos 的值为 -1 或者链表中的一个有效索引

// 进阶：你是否可以使用 O(1) 空间解决此题？



// #142. 环形链表 II
// 题意：给定一个链表，返回链表开始入环的第一个节点。如果链表无环，则返回 null。
// 为了表示给定链表中的环，使用整数 pos来表示链表尾连接到链表中的位置(索引从0开始)。
// 如果 pos是-1，则在该链表中没有环。

#include <iostream>
#include <unordered_set>
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
    ListNode *detectCycle(ListNode *head) {
        
    }
};



/////////////////////////// G1 哈希表

ListNode * detectCircle_G1(ListNode * head)
{
    unordered_set<ListNode *> visited;
    while(head != nullptr)
    {
        visited.insert(head);
        head = head->next;
        if(visited.count(head))
            return head;
    }
    return nullptr;
}

/////////////////////////// G2 双指针
// 解题思路：
// https://leetcode.cn/problems/linked-list-cycle-ii/solution/linked-list-cycle-ii-kuai-man-zhi-zhen-shuang-zhi-/
// 复杂度分析
// ·时间复杂度：O(N)，其中N为链表中节点的数目。在最初判断快慢指针是否相遇时，slow指针走过
// 的距离不会超过链表的总长度；随后寻找入环点时，走过的距离也不会超过链表的总长度。因此，总的
// 执行时间为O(N)+O(N)=O(N)。
// ·空间复杂度：O(1)。我们只使用了slow，fast两个指针。

ListNode * detectCircle_G2(ListNode * head)
{
    ListNode * fast = head;
    ListNode * slow = head;
    while(fast != nullptr)
    {
        if(fast->next == nullptr)   // 不能继续 next了
            return nullptr;
        fast = fast->next->next;    // 快走两步
        slow = slow->next;          // 慢走一步
        if(fast == slow)            // 有环时，slow再走 a步到环入口
        {
            fast = head;
            while(fast != slow)
            {
                fast = fast->next;
                slow = slow->next;
            }
            return fast;
        }
    }
    return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 18:32--18:36--18:38
// hash
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> hash;
        ListNode* cur = head;
        while(!hash.count(cur) && cur != nullptr) {  // 没找到 且 没到结尾      ***
            hash.insert(cur);
            cur = cur->next;
        }
        return cur; // 找到了 或 到了结尾
    }
};



class Solution_S2_D1_copy {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            // 快慢指针相遇，此时从head 和 相遇点，同时查找直至相遇
            if (slow == fast) {
                ListNode* index1 = fast;
                ListNode* index2 = head;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2; // 返回环的入口
            }
        }
        return NULL;
    }
};