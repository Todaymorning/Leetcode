// 977. 有序数组的平方
// https://leetcode.cn/problems/squares-of-a-sorted-array/description/
// 思路
// 简单
// 给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。

// 示例 1：
// 输入：nums = [-4,-1,0,3,10]
// 输出：[0,1,9,16,100]
// 解释：平方后，数组变为 [16,1,0,9,100]
// 排序后，数组变为 [0,1,9,16,100]

// 示例 2：
// 输入：nums = [-7,-3,2,3,11]
// 输出：[4,9,9,49,121]

// 提示：
// 1 <= nums.length <= 10^4
// -10^4 <= nums[i] <= 10^4
// nums 已按 非递减顺序 排序

// 进阶：
// 请你设计时间复杂度为 O(n) 的算法解决本问题

#include <iostream>
#include <vector>
#include <algorithm>    // sort()
using namespace std;

// 977. 有序数组的平方
// 给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，
// 要求也按 非递减顺序 排序。
// 示例 1： 输入：nums = [-4,-1,0,3,10] 输出：[0,1,9,16,100] 解释：平方后，数组变为 [16,1,0,9,100]，排序后，数组变为 [0,1,9,16,100]
// 示例 2： 输入：nums = [-7,-3,2,3,11] 输出：[4,9,9,49,121]

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {

    }
};


// 暴力排序：tO(n+nlogn)
vector<int> sortedSquares1(vector<int> & nums)
{
    int count = nums.size();
    for(int i=0; i<count; i++)
    {
        nums[i] = nums[i]*nums[i];
    }
    sort(nums.begin(), nums.end()); // 快速排序
    return nums;
}

// 双指针法：
// 非递减顺序数组，平方的最大值将出现在两端，中间最小
vector<int> sortedSquares2(vector<int> & nums)
{
    int count = nums.size();
    int Index = count - 1;
    vector<int> result(count, 0);
    int left, right;
    for(int i=0, j=count-1; i<=j;)
    {
        left = nums[i] * nums[i];
        right = nums[j] * nums[j];
        if(left > right)
        {
            result[Index--] = left;
            i++;
        }
        else
        {
            result[Index--] = right;
            j--;
        }
    }
    return result;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 18:31--18:35
// while
class Solution_S2_M1 {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        int idx = right;
        vector<int> result(nums.size(), 0);
        while(left <= right) {
            int l = nums[left] * nums[left];
            int r = nums[right] * nums[right];
            if(l > r) {
                result[idx--] = l;
                left++;
            }
            else {
                result[idx--] = r;
                right--;
            }
        }
        return result;
    }
};

// for
class Solution_S2_M2 {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int idx = nums.size() - 1;
        vector<int> result(nums.size(), 0);
        int left, right;
        for(int i=0, j=idx; i<=j; idx--) {
            left = nums[i] * nums[i];
            right = nums[j] * nums[j];
            if(left > right) {
                result[idx] = left;
                i++;
            }
            else {
                result[idx] = right;
                j--;
            }
        }
        return result;
    }
};