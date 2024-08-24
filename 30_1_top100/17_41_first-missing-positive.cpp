// https://leetcode.cn/problems/first-missing-positive/description/?envType=study-plan-v2&envId=top-100-liked//
// 41. 缺失的第一个正数
// 困难
// 相关标签
// 相关企业
// 提示
// 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。

// 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
 

// 示例 1：

// 输入：nums = [1,2,0]
// 输出：3
// 解释：范围 [1,2] 中的数字都在数组中。
// 示例 2：

// 输入：nums = [3,4,-1,1]
// 输出：2
// 解释：1 在数组中，但 2 没有。
// 示例 3：

// 输入：nums = [7,8,9,11,12]
// 输出：1
// 解释：最小的正数 1 没有出现。
 

// 提示：

// 1 <= nums.length <= 105
// -231 <= nums[i] <= 231 - 1




#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {

    }
};

// 1
// 我们可以将数组所有的数放入哈希表，随后从 1 开始依次枚举正整数，并判断其是否在哈希表中；
// 时间复杂度为 O(N)，空间复杂度为 O(N)

// 2
// 我们可以从 1 开始依次枚举正整数，并遍历数组，判断其是否在数组中。
// 时间复杂度为 O(N^2)空间复杂度为 O(1)

// 3
// 「真正」满足时间复杂度为 O(N) 且空间复杂度为 O(1) 的算法是不存在的，
// 但是我们可以退而求其次：利用给定数组中的空间来存储一些状态。
// 也就是说，如果题目给定的数组是不可修改的，那么就不存在满足时空复杂度要求的算法；
// 但如果我们可以修改给定的数组，那么是存在满足要求的算法的。


// 本地 hash
// 对于一个长度为 N 的数组，其中没有出现的最小正整数只能在 [1,N+1] 中。
// 这是因为如果 [1,N] 都出现了，那么答案是 N+1，否则答案是 [1,N]
// 先遍历一遍，将数组中不满足要求的数（负数和零）全部变成 N + 1
// 然后用负号作为标志，找到哪个正数就给数组中对应位置的数乘以一个负号
// 23:07--23:23
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int N = nums.size();
        for(int i=0; i<N; i++) {
            if(nums[i]<=0) nums[i] = N+1;
        }
        for(int i=0; i<N; i++) {
            // ***
            int num = std::abs(nums[i]); // 前面遍历了以后，后面的可能已经被乘以 -1 了
            if(num<=N) nums[num - 1] = -std::abs(nums[num - 1]);    // *** 防止有数字重复，偶数个重复的话会被乘正
        }
        for(int i=0; i<N; i++) {
            if(nums[i]>0) return i+1;   // ***
        }
        return N+1;
    }
};