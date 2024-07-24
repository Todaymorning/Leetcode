// 1005. K 次取反后最大化的数组和
// 简单
// 给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：
// 选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
// 重复这个过程恰好 k 次。可以多次选择同一个下标 i 。
// 以这种方式修改数组后，返回数组 可能的最大和 。

// 示例 1：
// 输入：nums = [4,2,3], k = 1
// 输出：5
// 解释：选择下标 1 ，nums 变为 [4,-2,3] 。

// 示例 2：
// 输入：nums = [3,-1,0,2], k = 3
// 输出：6
// 解释：选择下标 (1, 2, 2) ，nums 变为 [3,1,0,2] 。

// 示例 3：
// 输入：nums = [2,-3,-1,5,-4], k = 2
// 输出：13
// 解释：选择下标 (1, 4) ，nums 变为 [2,3,-1,5,4] 。
 
// 提示：
// 1 <= nums.length <= 10^4
// -100 <= nums[i] <= 100
// 1 <= k <= 10^4


#include<iostream>
#include<vector>
#include<algorithm>
using std::sort;
using std::vector;
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        return 0;
    }
};


// 10:57--11:26(min_idx)--11:35
// 排序后从小到大
// 有正有负，全正，全负，有没有 0
class Solution_M1 {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int neg = 0;        // 负数的个数
        int zer_idx = -1;   // 0 的索引
        int min_idx = -1;   // 没 0 时，绝对值最小的索引
        for(int i=0; i<int(nums.size()); i++) {
            if(nums[i] < 0) neg++;
            else if(nums[i] == 0) zer_idx = i;
            else if(i>0 && nums[i-1] < 0 && nums[i] >0) min_idx = (-nums[i-1]) < nums[i] ? i-1 : i;
            else break;
        }
        // ***
        if(min_idx == -1) {
            if(nums[0] >= 0) min_idx = 0;
            if(nums.back() <= 0) min_idx = nums.size() - 1;
        }

        if(k<=neg) { // k<=neg
            // 从开头翻转 k 个负数
            for(int i=0; i<k; i++) {
                nums[i] = -nums[i];
            }
        }
        else {  // k>neg
            if(zer_idx != -1) { // 有 0
                // 翻转所有负数
                for(int i=0; i<neg; i++) {
                    nums[i] = -nums[i];
                }
                // 剩下的翻转 0
            }
            else {  // 无 0
                // 翻转所有负数
                for(int i=0; i<neg; i++) {
                    nums[i] = -nums[i];
                }
                k-=neg;
                if(k%2 != 0) {  // 翻转绝对值最小的数   ***
                    if(min_idx != -1) nums[min_idx] = -nums[min_idx];
                    else nums[0] = -nums[0];
                }
            }
        }

        int sum = 0;
        for(int i:nums) {
            sum += i;
        }
        
        return sum;
    }
};


// D1
// 贪心的思路，局部最优：让绝对值大的负数变为正数，当前数值达到最大，整体最优：整个数组和达到最大。局部最优可以推出全局最优。
// 那么如果将负数都转变为正数了，K 依然大于 0，此时的问题是一个有序正整数序列，如何转变 K 次正负，让 数组和 达到最大。
// 那么又是一个贪心：局部最优：只找数值最小的正整数进行反转，当前数值和可以达到最大
// 1.按绝对值从大到小排序
// 2.从开头开始翻转负数
// 3.如果k还没反转完，就翻转最后一个数
class Solution_D1 {
    static bool cmp(int a, int b) {
        return abs(a) > abs(b);
    }
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), cmp);    // 按绝对值从大到小排序
        for(int i=0; i<nums.size(); i++) {      // 从头开始翻转负数
            if(nums[i] < 0 && k > 0) {
                nums[i] *= -1;
                k--;
            }
        }
        if(k%2 == 1) nums.back() *= -1;
        int result = 0;
        for(int i:nums) result += i;
        return result;
    }
};