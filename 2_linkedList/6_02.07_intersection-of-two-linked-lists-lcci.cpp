// 面试题 02.07. 链表相交
// https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/
// 简单
// 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null 。
// 题目数据 保证 整个链式结构中不存在环。
// 注意，函数返回结果后，链表必须 保持其原始结构 。

// 示例 1：
// 输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
// 输出：Intersected at '8'
// 解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
// 从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。
// 在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。

// 示例 2：
// 输入：intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
// 输出：Intersected at '2'
// 解释：相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。
// 从各自的表头开始算起，链表 A 为 [0,9,1,2,4]，链表 B 为 [3,2,4]。
// 在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。

// 示例 3：
// 输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
// 输出：null
// 解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
// 由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
// 这两个链表不相交，因此返回 null 。

// 提示：
// listA 中节点数目为 m
// listB 中节点数目为 n
// 0 <= m, n <= 3 * 10^4
// 1 <= Node.val <= 10^5
// 0 <= skipA <= m
// 0 <= skipB <= n
// 如果 listA 和 listB 没有交点，intersectVal 为 0
// 如果 listA 和 listB 有交点，intersectVal == listA[skipA + 1] == listB[skipB + 1]

// 进阶：你能否设计一个时间复杂度 O(n) 、仅用 O(1) 内存的解决方案？



// 面试题 02.07. 链表相交
// 同：160. 链表相交
// 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。
// 如果两个链表没有交点，返回 null

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

/////////////////////////// G1 哈希集合:
// 判断两个链表是否相交，可以使用哈希集合存储链表节点。
// 首先遍历链表 headA，并将链 表headA中的每个节点加入哈希集合中。然后遍历链表 headB，对于遍历到的
// 每个节点，判断该节点是否在哈希集合中：
// ·如果当前节点不在哈希集合中，则继续遍历下一个节点；
// ·如果当前节点在哈希集合中，则后面的节点都在哈希集合中，即从当前节点开始的所有节点都在两个链
// 表的相交部分，因此在链表 headB中遍历到的第一个在哈希集合中的节点就是两个链表相交的节点，
// 返回该节点。
// 如果链表 headB中的所有节点都不在哈希集合中，则两个链表不相交，返回 null。
// 
// 复杂度分析
// ·时间复杂度：O(m+n)，其中m和n是分别是链表headA和headB的长度。需要遍历两个链表各一
// ·空间复杂度：O(m)，其中m是链表headA的长度。需要使用哈希集合存储链表head4中的全部节点。

ListNode * getIntersectionNode_G1(ListNode * headA, ListNode * headB)
{
    unordered_set<ListNode *> visited;  // 无序集合，存放地址
    ListNode * temp = headA;
    while(temp != nullptr)              // 遍历 A
    {
        visited.insert(temp);
        temp = temp->next;
    }
    temp = headB;
    while(temp != nullptr)
    {
        if(visited.count(temp))         // 找到交点
            return temp;
        temp = temp->next;
    }
    return nullptr;                     // 未找到交点
}

/////////////////////////// G2 双指针法：
// 只有当链表 headA和 headB都不为空时，两个链表才可能相交。
// 因此首先判断链表 headA和 headB是否为空，如果其中至少有一个链表为空，则两个链表一定不相交，返回 null。
// 当链表 headA和 headB都不为空时，创建两个指针 pA和 pB，初始时分别指向两个链表的头节点 headA和 headB，
// 然后将两个指针依次遍历两个链表的每个节点。具体做法如下：
// ·每步操作需要同时更新指针 pA和 pB。
// ·如果指针 pA不为空，则将指针 pA移到下一个节点；如果指针 pB不为空，则将指针 pB移到下一个节点。
// ·如果指针 pA为空，则将指针 pA移到链表 headB的头节点；
//  如果指针 pB为空，则将指针 pB移到链表 headA的头节点。
// ·当指针 pA和 pB指向同一个节点或者都为空时，返回它们指向的节点或者 nul。
// · 时间复杂度：O(m+n)，其中m和n是分别是链表 headA和 headB的长度。
//   两个指针同时遍历两个链表，每个指针遍历两个链表各一次。
// · 空间复杂度：O(1)。

ListNode * getIntersectionNode_G2(ListNode * headA, ListNode * headB)
{
    if(headA == nullptr || headB == nullptr)
        return nullptr;
    ListNode * pA = headA;
    ListNode * pB = headB;
    while(pA != pB)
    {
        pA = (pA == nullptr) ? headB : pA->next;
        pB = (pB == nullptr) ? headA : pB->next;
    }
    return pA;  // 有交点这里返回的就是交点，没有交点时 pA == pB == nullptr 才从上面的循环跳出
}



// 不推荐
// 我们求出两个链表的长度，并求出两个链表长度的差值，然后让 curA 移动到，和 curB 末尾对齐的位置，
// 此时我们就可以比较 curA 和 curB 是否相同，如果不相同，同时向后移动 curA 和 curB，如果遇到 curA == curB，则找到交点。
// 否则循环退出返回空指针。
class Solution_S2_D1_copy {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* curA = headA;
        ListNode* curB = headB;
        int lenA = 0, lenB = 0;
        while (curA != NULL) { // 求链表A的长度
            lenA++;
            curA = curA->next;
        }
        while (curB != NULL) { // 求链表B的长度
            lenB++;
            curB = curB->next;
        }
        curA = headA;
        curB = headB;
        // 让curA为最长链表的头，lenA为其长度
        if (lenB > lenA) {
            swap (lenA, lenB);
            swap (curA, curB);
        }
        // 求长度差
        int gap = lenA - lenB;
        // 让curA和curB在同一起点上（末尾位置对齐）
        while (gap--) {
            curA = curA->next;
        }
        // 遍历curA 和 curB，遇到相同则直接返回
        while (curA != NULL) {
            if (curA == curB) {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return NULL;
    }
};



// 2024年5月20日
// 21:23--21:32
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* A = headA;
        ListNode* B = headB;
        int numA = 1;
        while(A->next != nullptr) {
            A = A->next;
            numA++;
        }
        int numB = 1;
        while(B->next != nullptr) {
            B = B->next;
            numB++;
        }
        if(A != B) return nullptr;
        int numL = std::max(numA, numB);
        int numS = std::min(numA, numB);
        ListNode* L = (numA > numB) ? headA : headB;
        ListNode* S = (L == headA) ? headB : headA;
        int diff = numL - numS;
        while(diff) {
            L = L->next;
            diff--;
        }
        while(L != S) {
            L = L->next;
            S = S->next;
        }
        return S;
    }
};