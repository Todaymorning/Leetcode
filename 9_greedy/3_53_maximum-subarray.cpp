// 53. 最大子数组和
// labuladong 题解思路
// 中等
// 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
// 子数组 是数组中的一个连续部分。

// 示例 1：
// 输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
// 输出：6
// 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。

// 示例 2：
// 输入：nums = [1]
// 输出：1

// 示例 3：
// 输入：nums = [5,4,-1,7,8]
// 输出：23

// 提示：
// 1 <= nums.length <= 10^5
// -10^4 <= nums[i] <= 10^4

// 进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。


#include<iostream>
#include<vector>
using std::vector;
class Solution {
public:
    int maxSubArray(vector<int>& nums) {

    }
};


// 15:38--15:48(错误，超出时间限制)--15:55(超出时间限制)
// 暴力解法
#if 0
class Solution_M1 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        int result = INT_MIN;
        for(int i=0; i<size; i++) {   // 设立起始位置
            for(int j=size-1; j>=i; j--){   // 尾
                int sum = 0;
                for(int k=i; k<=j; k++) {
                    sum += nums[k];
                }
                result  = result > sum ? result : sum;
            }
        }
        return result;
    }
};

// 比上面的快，但是还是超出时间限制
class Solution_D1_M1 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        int sum = 0;
        int result = 0;
        for(int i=0; i<size; i++) { // 设立起始位置
            sum = 0;
            for(int j=i; j<size; j++) { // 从起始位置开始寻找最大值
                sum += nums[j];
                result = result > sum ? result : sum;
            }
        }
        return result;
    }
};
#endif



// 15:33--15:38(没思路)--15:55(看暴力解法)--16:18(贪心解法)
// 贪心解法
// 贪心贪的是哪里呢？
// 如果 -2 1 在一起，计算起点的时候，一定是从 1 开始计算，因为负数只会拉低总和，这就是贪心贪的地方！
// 局部最优：当前 “连续和” 为负数的时候立刻放弃，从下一个元素重新计算 “连续和”，因为负数加上下一个元素 “连续和” 只会越来越小。
// 全局最优：选取最大 “连续和”
// 局部最优的情况下，并记录最大的 “连续和”，可以推出全局最优。
// 连续和为负的，那么这段就没有和后面累加的价值
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution_D2_M1 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        int result = INT_MIN;
        int sum = 0;
        // 为什么不是前一个序列中后面某一部分加上继续往下走的序列和最大？
        // sum是从0开始计算的，如果序列中后面某一部分之和大于0，加上前面的就更大了，没道理只取后面不加前面，所以前面的直接舍弃
        for(int i=0; i<size; i++) {
            sum += nums[i]; // sum为连续子序列的和
            if(sum > result) {
                result = sum;
            }
            if(sum <= 0) sum = 0;   // 一旦连续子序列的和为0，重新开始子序列
        }
        return result;
    }
};


// 动态规划
// 见动态规划 34