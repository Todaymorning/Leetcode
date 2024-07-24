// https://leetcode.cn/problems/reverse-nodes-in-k-group
// 25. K 个一组翻转链表
// labuladong 题解
// 思路
// 困难
// 相关标签
// 相关企业
// 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
// k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
// 你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。

// 示例 1：
// 输入：head = [1,2,3,4,5], k = 2
// 输出：[2,1,4,3,5]

// 示例 2：
// 输入：head = [1,2,3,4,5], k = 3
// 输出：[3,2,1,4,5]

// 提示：
// 链表中的节点数目为 n
// 1 <= k <= n <= 5000
// 0 <= Node.val <= 1000


#include<iostream>
#include<vector>
#include<string>
using std::string;
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
    ListNode* reverseKGroup(ListNode* head, int k) {

    }
};



// 16:08--16:24--16:32
#if 0
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int num = 0;
        ListNode* dummy = new ListNode();
        ListNode* left, *right;
        dummy->next = head;
        left = dummy;
        right = dummy;
        while(right != nullptr) {
            bool need = true;
            // right 向后移动 k
            for(int i=0; i<k; i++) {
                if(right != nullptr) {
                    right = right->next;
                }
                else {
                    need = false;
                }
            }
            // 有 k 个需要翻转
            if(need) {
                ListNode* pre = right->next;
                ListNode* cur = left->next;
                ListNode* temp;
                while(cur != right) {
                    temp = cur->next;   // 保存
                    cur->next = pre;    // 反向
                    pre = cur;          // 下一组
                    cur = temp;
                }
            }
            left = right;
        }
        return dummy->next;
    }
};

int main() {
    ListNode* head = new ListNode(1);
    ListNode* cur = head;
    for(int i=2; i<=5; i++) {
        cur->next = new ListNode(i);
        cur = cur->next;
    }
    Solution ss;
    ss.reverseKGroup(head, 3);
    return 0;
}
#endif


// 10:08--10:17
class Solution {
    // 翻转 [a, b)， b 可以为 nullptr，最终返回 b 的前一个节点
    ListNode* reverse(ListNode* a, ListNode* b) {
        ListNode* pre = nullptr;
        ListNode* cur = a;
        ListNode* tmp;
        while(cur != b) {
            tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* left = head;
        ListNode* right = head;
        for(int i=0; i<k; i++) {
            if(right == nullptr) return head;   // 不够 k 个
            right = right->next;
        }
        // 翻转前 k 个节点
        ListNode* newHead = reverse(left, right);
        // 翻转后的尾节点为 left，翻转剩余节点并连接首尾
        left->next = reverseKGroup(right, k);
        return newHead;
    }
};










// // 34
// class Solution {
// public:
//     vector<int> searchRange (vector<int>& nums, int target) {
//         int size = nums.size ();
//         int left = 0, right = size-1; // []
//         int mid;
//         while (left <= right) {
//             mid = left + (right - left) / 2;
//             // 缩小范围
//             if (nums [mid] > target) {
//                 right = mid - 1;
//             }
//             else if (nums [mid] < target) {
//                 left = mid + 1;
//             }
//             else {
//                 left = mid;
//                 right = mid;
//                 while (left >= 0 && nums [left] == target) left--;
//                 while (right <= size-1 && nums [right] == target) right++;
//                 return vector<int>{left+1, right-1};
//             }
//         }
//         return vector<int>{-1, -1};
//     }
// };




// #include<iostream>
// #include<string>
// using std::string;
// using std::max;
// // 19:15
// class Solution {
// public:
//     string addStrings(string num1, string num2) {
//         string result;
//         int size1 = num1.size();
//         int size2 = num2.size();
//         int low = num1.back() - '0' + num2.back() - '0';
//         int high = low / 10;
//         low %= 10;
//         for(int i=2; i<=max(size1, size2); i++) {
//             result.push_back(low + '0');
//             int temp1 = 0, temp2 = 0;
//             if(i <= size1) {
//                 temp1 = num1[size1 - i] - '0';
//             }
//             if(i <= size2) {
//                 temp2 = num2[size2 - i] - '0';
//             }
//             low = temp1 + temp2 + high;
//             high = low / 10;
//             low %= 10;
//         }
//         result.push_back(low + '0');
//         if(high) result.push_back(high + '0');
//         for(int i=0; i<result.size()/2; i++) {
//             char temp = result[i];
//             result[i] = result[result.size() - i -1];
//             result[result.size() - i - 1] = temp;
//         }
//         return result;
//     }
// };