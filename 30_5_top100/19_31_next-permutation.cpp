// https://leetcode.cn/problems/next-permutation/description/
// 31. 下一个排列
// 已解答
// 中等
// 相关标签
// 相关企业
// 整数数组的一个 排列  就是将其所有成员以序列或线性顺序排列。

// 例如，arr = [1,2,3] ，以下这些都可以视作 arr 的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1] 。
// 整数数组的 下一个排列 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 下一个排列 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。

// 例如，arr = [1,2,3] 的下一个排列是 [1,3,2] 。
// 类似地，arr = [2,3,1] 的下一个排列是 [3,1,2] 。
// 而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1] 不存在一个字典序更大的排列。
// 给你一个整数数组 nums ，找出 nums 的下一个排列。

// 必须 原地 修改，只允许使用额外常数空间。

 

// 示例 1：

// 输入：nums = [1,2,3]
// 输出：[1,3,2]
// 示例 2：

// 输入：nums = [3,2,1]
// 输出：[1,2,3]
// 示例 3：

// 输入：nums = [1,1,5]
// 输出：[1,5,1]
 

// 提示：

// 1 <= nums.length <= 100
// 0 <= nums[i] <= 100


#include<iostream>
#include<vector>
using std::vector;


class Solution {
public:
    void nextPermutation(vector<int>& nums) {

    }
};


// 解法
// https://leetcode.cn/problems/next-permutation/solutions/80560/xia-yi-ge-pai-lie-suan-fa-xiang-jie-si-lu-tui-dao-/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if(nums.size() <= 1) return;
        // 从后往前找两相邻升序元素对：nums[i] < nums[i+1]
        // 从后往前找一个大于nums[i]的数，nums[i] < nums[j] j > i
        // 交换 std::swap(nums[i], nums[j]);
        // 将[i+1, end]反转
        for(int i=nums.size() - 2; i>=0; i--) {
            // 从后往前找 ^ 的结构，交换后后面的肯定是降序
            if(nums[i] < nums[i+1]) {
                for(int j=nums.size()-1; j>i; j--) {
                    if(nums[i] < nums[j]) {
                        std::swap(nums[i], nums[j]);
                        // 将后面的降序重新升序（反转）尽量降低字典序
                        int left = i+1;
                        int right = nums.size() - 1;
                        while(left < right) {
                            std::swap(nums[left++], nums[right--]);
                        }
                        return;
                    }
                }
            }
        }
        // 如果没有找到，则证明整个数组是降序的，需要整个倒序
        int left = 0, right = nums.size() - 1;
        while(left<right) {
            std::swap(nums[left++], nums[right--]);
        }
        return;
    }
};