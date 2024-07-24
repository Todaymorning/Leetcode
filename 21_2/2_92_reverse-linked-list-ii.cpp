// https://leetcode.cn/problems/reverse-linked-list-ii
// 92. 反转链表 II
// labuladong 题解
// 思路
// 中等
// 相关标签
// 相关企业
// 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。

// 示例 1：
// 输入：head = [1,2,3,4,5], left = 2, right = 4
// 输出：[1,4,3,2,5]

// 示例 2：
// 输入：head = [5], left = 1, right = 1
// 输出：[5]

// 提示：
// 链表中节点数目为 n
// 1 <= n <= 500
// -500 <= Node.val <= 500
// 1 <= left <= right <= n

// 进阶： 你可以使用一趟扫描完成反转吗？


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


class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {

    }
};



//*****************************************************************************************************************************
// 2024年4月30日
// 18:52--19:11--19:20--解决
// 输入
// head =
// [3,5]
// left =
// 1
// right =
// 2
// 输出
// [3]
// 预期结果
// [5,3]
class Solution_M1 {
    // 翻转 [left, right), right 可以等于 nullptr
    ListNode* reverse(ListNode* left, ListNode* right) {
        ListNode* pre = nullptr;
        ListNode* cur = left;
        ListNode* temp;
        while(cur != right) {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre; // 返回新的头节点：原来 right 的前一个节点
    }
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(left == right) return head;
        // 找到左侧节点 l 和其前一个节点 pre
        ListNode* l = head;
        ListNode* pre = nullptr;
        int idx = 1;
        while(idx < left) {
            if(idx == left - 1) {
                pre = l;
            }
            l = l->next;
            idx++;
        }
        // 找到右侧节点的下一节点 r
        ListNode* r = l;
        while(idx <= right) {
            r = r->next;
            idx++;
        }
        // 翻转 [l, r)
        ListNode* h = reverse(l, r);
        // 连接 pre --> l 和 l --> r
        if(pre != nullptr) {
            pre->next = h;
        }
        l->next = r;
        return pre == nullptr ? h : head;   // ***
    }
};


// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/reverse-linked-list-ii/solutions/634701/fan-zhuan-lian-biao-ii-by-leetcode-solut-teyq/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_G1_copy {
private:
    // 这里只是单纯的翻转链表，没有返回头节点
    void reverseLinkedList (ListNode *head) {
        // 也可以使用递归反转一个链表
        ListNode *pre = nullptr;
        ListNode *cur = head;
        ListNode *next;
        while (cur != nullptr) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
    }

public:
    ListNode *reverseBetween (ListNode *head, int left, int right) {
        // 因为头节点有可能发生变化，使用虚拟头节点可以避免复杂的分类讨论
        ListNode *dummyNode = new ListNode (-1);
        dummyNode->next = head;

        ListNode *pre = dummyNode;
        // 第 1 步：从虚拟头节点走 left - 1 步，来到 left 节点的前一个节点
        // 建议写在 for 循环里，语义清晰
        for (int i = 0; i < left - 1; i++) {
            pre = pre->next;
        }

        // 第 2 步：从 pre 再走 right - left + 1 步，来到 right 节点
        ListNode *rightNode = pre;
        for (int i = 0; i < right - left + 1; i++) {
            rightNode = rightNode->next;
        }

        // 第 3 步：切断出一个子链表（截取链表）
        ListNode *leftNode = pre->next;
        ListNode *curr = rightNode->next;

        // 注意：切断链接
        pre->next = nullptr;
        rightNode->next = nullptr;

        // 第 4 步：同第 206 题，反转链表的子区间
        reverseLinkedList (leftNode);

        // 第 5 步：接回到原来的链表中
        pre->next = rightNode;
        leftNode->next = curr;
        return dummyNode->next;
    }
};




// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/reverse-linked-list-ii/solutions/634701/fan-zhuan-lian-biao-ii-by-leetcode-solut-teyq/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_G2_copy {
public:
    ListNode *reverseBetween (ListNode *head, int left, int right) {
        // 设置 dummyNode 是这一类问题的一般做法
        ListNode *dummyNode = new ListNode (-1);
        dummyNode->next = head;
        ListNode *pre = dummyNode;
        // 找到 left 前一个节点 pre
        for (int i = 0; i < left - 1; i++) {
            pre = pre->next;
        }
        ListNode *cur = pre->next;
        ListNode *next;
        for (int i = 0; i < right - left; i++) {
            next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }
        return dummyNode->next;
    }
};






// 2024 年 5 月 18 日
// 19:37--19:59
class Solution {
    // 翻转 [left, right)， right可以为 nullptr
    ListNode* reverse (ListNode* left, ListNode* right) {
        ListNode* pre = nullptr;
        ListNode* cur = left;
        ListNode* temp;
        while (cur != right) {
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre; // 返回新的头节点
    }
public:
    ListNode* reverseBetween (ListNode* head, int left, int right) {
        ListNode* dummyHead = new ListNode (0);
        dummyHead->next = head;
        ListNode* pre = dummyHead;    // left 前一个节点
        for (int i=0; i<left-1; i++) {
            pre = pre->next;
        }
        ListNode* leftNode = pre->next;
        ListNode* nex = pre;    //right 后一个节点
        for (int i=left-1; i<=right; i++) {
            nex = nex->next;
        }
        ListNode* h = reverse (leftNode, nex);
        pre->next = h;
        leftNode->next = nex;
        return dummyHead->next;
    }
};