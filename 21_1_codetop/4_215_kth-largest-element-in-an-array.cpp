// https://leetcode.cn/problems/kth-largest-element-in-an-array
// 215. 数组中的第 K 个最大元素
// labuladong 题解
// 思路
// 中等
// 相关标签
// 相关企业
// 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
// 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

// 示例 1:
// 输入: [3,2,1,5,6,4], k = 2
// 输出: 5

// 示例 2:
// 输入: [3,2,3,1,2,4,5,5,6], k = 4
// 输出: 4

// 提示：
// 1 <= k <= nums.length <= 10^5
// -10^4 <= nums[i] <= 10^4


#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using std::priority_queue;
using std::vector;



class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        
    }
};



// 11:31--11:38
// 小顶堆
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, std::greater<int>> pq; // greater
        int size = nums.size();
        for(int i=0; i<k; i++) {
            pq.push(nums[i]);
        }
        for(int i=k; i<size; i++) {
            if(nums[i] > pq.top()) {
                pq.pop();
                pq.push(nums[i]);
            }
        }
        return pq.top();
    }
};