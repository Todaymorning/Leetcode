// https://leetcode.cn/problems/merge-k-sorted-lists
// 23. 合并 K 个升序链表
// labuladong 题解
// 思路
// 困难
// 相关标签
// 相关企业
// 给你一个链表数组，每个链表都已经按升序排列。
// 请你将所有链表合并到一个升序链表中，返回合并后的链表。

// 示例 1：
// 输入：lists = [[1,4,5],[1,3,4],[2,6]]
// 输出：[1,1,2,3,4,4,5,6]
// 解释：链表数组如下：
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// 将它们合并到一个有序链表中得到。
// 1->1->2->3->4->4->5->6

// 示例 2：
// 输入：lists = []
// 输出：[]

// 示例 3：
// 输入：lists = [[]]
// 输出：[]

// 提示：
// k == lists.length
// 0 <= k <= 10^4
// 0 <= lists[i].length <= 500
// -10^4 <= lists[i][j] <= 10^4
// lists[i] 按 升序 排列
// lists[i].length 的总和不超过 10^4


#include<iostream>
#include<vector>
#include<queue>
#include<functional>
using std::function;
using std::priority_queue;
using std::vector;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};





class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

    }
};




// 2024年5月20日
// 20:13--20:36(错误的循环条件)
#if 0
class Solution {
    struct Cmp {
        bool operator()(const ListNode* a, const ListNode* b) {
            return a->val > b->val; // > 小顶堆
        }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 升序用小顶堆
        priority_queue<ListNode*, vector<ListNode*>, Cmp> pq;
        int num = lists.size();
        vector<int> empty(num, 0);
        ListNode* dummyHead = new ListNode(0);
        ListNode* cur = dummyHead;
        while(num > 0) {
            for(int i=0; i<lists.size(); i++) {
                // 遇到一个空的链表
                if(empty[i] == 1) continue;
                if(lists[i] == nullptr && empty[i] == 0) {
                    empty[i] = 1;
                    num--;
                    continue;
                }
                if(lists[i] == nullptr) continue;
                pq.emplace(lists[i]);
                lists[i] = lists[i]->next;
            }
            
            if(!pq.empty()) {
                cur->next = pq.top();
                pq.pop();
                cur = cur->next;
            }
        }
        return dummyHead->next;
    }
};
#endif


// 2024年5月20日
// 20:36--20:47(报错，不应该在lists中操作)
// eap-use-after-free
# if 0
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, function<bool (const ListNode*, const ListNode*)>> pq(
            [](const ListNode* a, const ListNode* b) {
                return a->val > b->val;
            }
        );
        for(int i=0; i<lists.size(); i++) {
            if(lists[i] != nullptr) {
                pq.emplace(lists[i]);
                lists[i] = lists[i]->next;
            }
        }
        ListNode* dummyHead = new ListNode(0);
        ListNode* cur = dummyHead;
        while(!pq.empty()) { // 循环条件，防止漏掉
            for(int i=0; i<lists.size(); i++) {
                if(lists[i] == nullptr) continue;
                pq.emplace(lists[i]);
                lists[i] = lists[i]->next;
            }
            cur->next = pq.top();
            cur = cur->next;
            pq.pop();
        }
        return dummyHead->next;
    }
};
#endif


// 2024年5月20日
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 小顶堆
        priority_queue<ListNode*, vector<ListNode*>, function<bool (const ListNode*, const ListNode*)>> pq(
            [](const ListNode* a, const ListNode* b) {
                return a->val > b->val;
            }
        );
        // 将有效头节点加入堆中
        for(int i=0; i<lists.size(); i++) {
            if(lists[i] != nullptr) {
                pq.emplace(lists[i]);
            }
        }
        // 虚拟头节点
        ListNode* dummyHead = new ListNode(0);
        // 当前节点，新节点需要往后接
        ListNode* cur = dummyHead;
        while(!pq.empty()) {
            // 从小顶堆中拿出最小的元素
            ListNode* temp = pq.top();
            pq.pop();
            // 接入结果链表
            cur->next = temp;
            // 移动
            cur = cur->next;
            // 最小元素的下一个加入堆
            if(temp->next != nullptr) pq.emplace(temp->next);
        }
        return dummyHead->next;
    }
};
