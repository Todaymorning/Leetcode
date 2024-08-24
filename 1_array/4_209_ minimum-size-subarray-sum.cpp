// 209. 长度最小的子数组
// https://leetcode.cn/problems/minimum-size-subarray-sum/
// 思路
// 中等
// 给定一个含有 n 个正整数的数组和一个正整数 target 。
// 找出该数组中满足其总和大于等于 target 的长度最小的 连续
// 子数组
//  [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

// 示例 1：
// 输入：target = 7, nums = [2,3,1,2,4,3]
// 输出：2
// 解释：子数组 [4,3] 是该条件下的长度最小的子数组。

// 示例 2：
// 输入：target = 4, nums = [1,4,4]
// 输出：1

// 示例 3：
// 输入：target = 11, nums = [1,1,1,1,1,1,1,1]
// 输出：0

// 提示：
// 1 <= target <= 10^9
// 1 <= nums.length <= 10^5
// 1 <= nums[i] <= 10^5

// 进阶：
// 如果你已经实现 O(n) 时间复杂度的解法，请尝试设计一个 O(n log(n)) 时间复杂度的解法。


#include <iostream>
#include <vector>
using namespace std;

// 209. 长度最小的子数组
// 给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，
// 并返回其长度。如果不存在符合条件的子数组，返回 0。
// 输入：s = 7, nums = [2,3,1,2,4,3] 输出：2 解释：子数组 [4,3] 是该条件下的长度最小的子数组

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {

    }
};


// 暴力求解：tO(n^2), sO(1)
// i 从 0 到 n 遍历， j 从 i 到 n 遍历
int minSubArrayLen1(int target, vector<int>& nums)
{
    int n = nums.size();
    // if(n == 0)
    //     return 0;
    int result = INT_MAX;   // 最终结果
    int subLength = 0;      // 子序列长度
    for(int i=0; i< n; i++)
    {
        int sum = 0;
        for(int j=i; j<n; j++)
        {
            sum += nums[i];
            if(sum >= target)
            {
                // result = min(result, j-i+1);
                subLength = j - i + 1;
                result = result < subLength ? result : subLength;
                break;
            }
        }
    }
    // 如果result没有被赋值的话，就返回0，说明没有符合条件的子序列
    return result == INT_MAX ? 0 : result;
}


// 滑动窗口：tO(n), sO(1)
// 滑动窗口也可以理解为双指针法的一种
// 滑动窗口的精妙之处在于根据当前子序列和大小的情况，不断调节子序列的起始位置。从而将 O (n^2) 暴力解法降为 O (n)。
int minSubarrayLen2(int target, vector<int> & nums)
{
    int n = nums.size();
    // int start = 0;  // 窗口起点
    // int end = 0;    // 窗口终点
    int subLength = 0;  // 窗口长度
    int sum = 0;        // 窗口内之和
    int result = INT_MAX;
    for(int start=0, end=0 ; end<n; end++)
    {
        sum += nums[end];
        while(sum >= target)
        {
            subLength = end - start + 1;
            result = result < subLength ? result : subLength;
            sum -= nums[start++];   // 更新起点和子序列的和 ***
        }
    }
    return result == INT_MAX ? 0 : result;
}

// 滑动窗口：指针 start 和 end 最多各移动 n 次
// start end 初始为 0；先移 start 再移 end
int minSubArrayLen3(int target, vector<int> & nums)
{
    int n = nums.size();
    int start = 0;
    int end = 0;
    int subLength = 0;
    int sum = 0;
    int result = INT_MAX;
    while(end < n)
    {
        sum += nums[end];
        while(sum >= target)
        {
            subLength = end - start + 1;
            result = result < subLength ? result : subLength;
            sum -= nums[start];
            start ++;
        }
        end++;
    }
    return result == INT_MAX ? 0 : result;
}

// 前缀和 + 二分查找：tO(logn)
// 数组全部为正，是二分查找的前提
// 用另外的数组存储 nums 数组的前缀和，然后用二分查找
int minSubArrayLen4(int target, vector<int> & nums)
{
    int n = nums.size();
    vector<int> ans(n + 1, 0);
    // 为了方便计算, 令 size = n + 1
    // sums[0]=0意味着前0个元素的前缀和为0
    // sums[1]=A[0]前1个元素的前缀和为A[0]
    int result = INT_MAX;
    for(int i=1; i<=n; i++) // 求前缀和
    {
        ans[i] = ans[i-1] + nums[i-1];
    }
    for(int i=1; i<=n; i++)
    {
        int temp = target + ans[i-1];   // 让窗口中间大于等于target，每次循环相当于窗口起点右移
        // lower_bound () 函数用于在指定区域内查找不小于目标值的第一个元素。
        auto bound = lower_bound(ans.begin(), ans.end(), temp); // 二分法
        if(bound != ans.end())
        {
            result = min(result, static_cast<int>((bound)-ans.begin()) - (i-1));
        }
    }
    return  result == INT_MAX ? 0 : result;
}

// 二分查找函数
// 查找数组 nums中大于等于 target 的最小值，返回其索引值，找不到返回 -1
// 其中 nums 单调不减
int LowerBound(vector<int> & nums, int target)
{
    int middle = -1;
    int left = 0;
    int right = nums.size();    // [left,right)
    // if(target > nums.back())
    //     return -1;
    while(left < right)
    {
        middle = left + ((right - left) >> 1);
        if(nums[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle;
        }
    }
    return left >= nums.size() ? -1 : left;
}

int minSubArrayLen5(int target, vector<int> & nums)
{
    int n = nums.size();
    vector<int> ans(n + 1, 0);
    int result = INT_MAX;
    for(int i=1; i<=n; i++)
    {
        ans[i] = ans[i-1] + nums[i-1];
    }
    for(int i=1; i<=n; i++)
    {
        int bound = LowerBound(ans, target + ans[i-1]);
        // cout << i << "bound: " << bound << endl;
        if(bound < n+1)
        {
            result = min(result, bound - i + 1);
        }
    }
    return result == INT_MAX ? 0 : result;
}


#if 1
int main()
{
    int target = 7;
    vector<int> nums = {2,3,1,2,4,3};
    cout << minSubArrayLen5(target, nums) << endl;
}
#endif




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 20:37--20:41(看题找思路)--21:04(中间错误好几次)
// 暴力解法——超时
class Solution_S2_M1 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int result = INT_MAX;   // ***
        for(int i=0; i<nums.size(); i++) {
            int sum = 0;
            for(int j=i; j<nums.size(); j++) {
                sum += nums[j];
                if(sum >= target) {
                    result = result < (j-i+1) ? result :(j-i+1);
                    break;
                }
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};


// 滑动窗口
// 
class Solution_S2_M2 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int result = INT_MAX;
        int subLength = 0;
        int sum = 0;
        // i 终点 j 起点
        for(int i=0, j=0; i<nums.size(); i++) {
            sum += nums[i];
            while(sum >= target) {
                subLength = i - j + 1;
                result = result < subLength ? result : subLength;
                sum -= nums[j++];   // 更新起点和子序列的和
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};