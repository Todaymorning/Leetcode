// https://leetcode.cn/problems/rotate-array/description/?envType=study-plan-v2&envId=top-100-liked
// 189. 轮转数组
// 已解答
// 中等
// 相关标签
// 相关企业
// 提示
// 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

// 示例 1:
// 输入: nums = [1,2,3,4,5,6,7], k = 3
// 输出: [5,6,7,1,2,3,4]
// 解释:
// 向右轮转 1 步: [7,1,2,3,4,5,6]
// 向右轮转 2 步: [6,7,1,2,3,4,5]
// 向右轮转 3 步: [5,6,7,1,2,3,4]

// 示例 2:
// 输入：nums = [-1,-100,3,99], k = 2
// 输出：[3,99,-1,-100]
// 解释: 
// 向右轮转 1 步: [99,-1,-100,3]
// 向右轮转 2 步: [3,99,-1,-100]

// 提示：
// 1 <= nums.length <= 105
// -231 <= nums[i] <= 231 - 1
// 0 <= k <= 105

// 进阶：
// 尽可能想出更多的解决方案，至少有 三种 不同的方法可以解决这个问题。
// 你可以使用空间复杂度为 O(1) 的 原地 算法解决这个问题吗？


#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    void rotate(vector<int>& nums, int k) {

    }
};

// 使用一个新数组 new[(i + k) % n] = nums[i];
// 使用三次翻转

// https://leetcode.cn/problems/rotate-array/solutions/683855/shu-zu-fan-zhuan-xuan-zhuan-shu-zu-by-de-5937/?envType=study-plan-v2&envId=top-100-liked
class Solution_E1 {
    // 翻转 [left, right]
    void reverse(vector<int>& vec, int left, int right) {
        while(left < right) {
            std::swap(vec[left], vec[right]);
            left++;
            right--;
        }
    }
public:
    void rotate(vector<int>& nums, int k) {
        reverse(nums, 0, nums.size() - 1);
        reverse(nums, 0, k % nums.size() - 1);
        reverse(nums, k % nums.size(), nums.size() - 1);
    }
};