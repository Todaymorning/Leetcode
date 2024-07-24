// https://leetcode.cn/problems/merge-sorted-array
// 88. 合并两个有序数组
// 思路
// 简单
// 相关标签
// 相关企业
// 提示
// 给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
// 请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。
// 注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。

// 示例 1：
// 输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
// 输出：[1,2,2,3,5,6]
// 解释：需要合并 [1,2,3] 和 [2,5,6] 。
// 合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。

// 示例 2：
// 输入：nums1 = [1], m = 1, nums2 = [], n = 0
// 输出：[1]
// 解释：需要合并 [1] 和 [] 。
// 合并结果是 [1] 。

// 示例 3：
// 输入：nums1 = [0], m = 0, nums2 = [1], n = 1
// 输出：[1]
// 解释：需要合并的数组是 [] 和 [1] 。
// 合并结果是 [1] 。
// 注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。

// 提示：
// nums1.length == m + n
// nums2.length == n
// 0 <= m, n <= 200
// 1 <= m + n <= 200
// -10^9 <= nums1[i], nums2[j] <= 10^9

// 进阶：你可以设计实现一个时间复杂度为 O(m + n) 的算法解决此问题吗？


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

    }
};


// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // 两个指针分别初始化在两个数组的最后一个元素（类似拉链两端的锯齿）
        int i = m - 1, j = n - 1;
        // 生成排序的结果（类似拉链的拉锁）
        int p = nums1.size() - 1;
        // 从后向前生成结果数组，类似合并两个有序链表的逻辑
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[p] = nums1[i];
                i--;
            } else {
                nums1[p] = nums2[j];
                j--;
            }
            p--;
        }
        // 可能其中一个数组的指针走到尽头了，而另一个还没走完
        // 因为我们本身就是在往 nums1 中放元素，所以只需考虑 nums2 是否剩元素即可
        while (j >= 0) {
            nums1[p] = nums2[j];
            j--;
            p--;
        }
    }
};


// 2024年4月30日
// 使用额外空间
// 0:03--0:19
class Solution_M1 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> merges(nums1.size());
        int idx1 = 0, idx2 = 0;
        for(int i=0; i<nums1.size(); i++) {
            if(idx1 >= m) {
                merges[i] = nums2[idx2++];
            }
            else if(idx2 >= n) {
                merges[i] = nums1[idx1++];
            }
            else if(nums1[idx1] < nums2[idx2]) {
                merges[i] = nums1[idx1++];
            }
            else{
                merges[i] = nums2[idx2++];
            }
        }
        for(int i=0; i<nums1.size();i++) {
            nums1[i] = merges[i];
        }
    }
};

// 2024年4月30日
// 原地操作，从后往前
class Solution_L1_M2 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1;
        int idx = nums1.size() - 1;
        while(i>=0 && j>=0) {
            if(nums1[i] < nums2[j]) {
                nums1[idx--] = nums2[j--];
            }
            else {
                nums1[idx--] = nums1[i--];
            }
        }
        while(j>=0) {
            nums1[idx--] = nums2[j--];
        }
    }
};
