// https://leetcode.cn/problems/sort-list/description/?envType=study-plan-v2&envId=top-100-liked
// 148. 排序链表
// 已解答
// 中等
// 相关标签
// 相关企业
// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

 

// 示例 1：


// 输入：head = [4,2,1,3]
// 输出：[1,2,3,4]
// 示例 2：


// 输入：head = [-1,5,3,4,0]
// 输出：[-1,0,3,4,5]
// 示例 3：

// 输入：head = []
// 输出：[]
 

// 提示：

// 链表中节点的数目在范围 [0, 5 * 104] 内
// -105 <= Node.val <= 105
 

// 进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？






#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// 题目的进阶问题要求达到 O(nlogn) 的时间复杂度和 O(1) 的空间复杂度，
// 时间复杂度是 O(nlogn) 的排序算法包括归并排序、堆排序和快速排序
// （快速排序的最差时间复杂度是 O(n^2)
// 其中最适合链表的排序算法是归并排序。



class Solution_M1 {
public:
    ListNode* sortList(ListNode* head) {
        if(head == nullptr) return head;
        vector<ListNode*> val;
        for(ListNode* cur = head; cur != nullptr; cur = cur->next) {
            val.push_back(cur);
        }
        sort(val.begin(), val.end(), [](ListNode* a, ListNode* b) {
            return a->val < b->val;
        });
        for(int i=0; i<val.size()-1; i++) {
            val[i]->next = val[i+1];
        }
        val.back()->next = nullptr;
        return val[0];
    }
};