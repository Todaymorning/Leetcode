// https://leetcode.cn/problems/max-consecutive-ones-iii
// 1004. 最大连续1的个数 III
// 思路
// 中等
// 相关标签
// 相关企业
// 提示
// 给定一个二进制数组 nums 和一个整数 k，如果可以翻转最多 k 个 0 ，则返回 数组中连续 1 的最大个数 。

// 示例 1：
// 输入：nums = [1,1,1,0,0,0,1,1,1,1,0], K = 2
// 输出：6
// 解释：[1,1,1,0,0,1,1,1,1,1,1]
// 粗体数字从 0 翻转到 1，最长的子数组长度为 6。

// 示例 2：
// 输入：nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
// 输出：10
// 解释：[0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
// 粗体数字从 0 翻转到 1，最长的子数组长度为 10。

// 提示：
// 1 <= nums.length <= 10^5
// nums[i] 不是 0 就是 1
// 0 <= k <= nums.length


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {

    }
};



// 2024年5月13日
// 窗口 right - left + 1
// 统计窗口中 0 / 1 的个数，讨论与 k 的关系
class Solution_M2 {
public:
    int longestOnes(vector<int>& nums, int k) {
        int size = nums.size();
        int res = 0;
        int windowZeroCount = 0;
        for(int left=0, right=0; right<size; right++) {
            // 统计窗口中 0 的个数
            if(nums[right] == 0) {
                windowZeroCount++;
            }
            // 0 的个数大于 k 时缩小窗口
            while(windowZeroCount > k) {
                if(nums[left]==0) {
                    windowZeroCount--;
                }
                left++;
            }
            res = std::max(res, right - left + 1);
        }
        return res;
    }
};


// 2024年5月12日
// 11:40--11:45(看到提示词滑动窗口)--12:00
// 这里的逻辑较为晦涩：
// 只有 nums[right] == 1 才计算一次窗口大小，
// nums[right] == 0 时消耗 k计算一次窗口大小，
// k消耗完后，右边遇到 1 计算窗口，右边遇到 0 就从左边移除一个 0，维护窗口中间只有 k 个0的状态
class Solution_M1 {
public:
    int longestOnes(vector<int>& nums, int k) {
        int size = nums.size();
        int res = 0;
        for(int left=0, right=0; right<size; right++) {
            if(nums[right] == 1) { // 1 增大窗口
                int temp = right - left + 1;
                if(temp > res) res = temp;
            }
            else if(k > 0) {    // 0 消耗次数增大窗口
                k--;
                int temp = right - left + 1;
                if(temp > res) res = temp;
            }
            else {  // k=0 没有次数：左边移除一个 0
                while(left < right && nums[left] == 1) {
                    left++;
                }
                if(left <= right && nums[left] == 0) {  // <=       // ***
                    left++;
                    // k++;
                    // right--;
                }
            }
        }
        return res;
    }
};




// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1 {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0, right = 0;
        // 记录窗口中 1 的出现次数
        int windowOneCount = 0;
        // 记录结果长度
        int res = 0;

        // 开始滑动窗口模板
        while (right < nums.size()) {
            // 扩大窗口
            if (nums[right] == 1) {
                windowOneCount++;
            }
            right++;

            while (right - left - windowOneCount > k) {
                // 当窗口中需要替换的 0 的数量大于 k，缩小窗口
                if (nums[left] == 1) {
                    windowOneCount--;
                }
                left++;
            }
            // 此时一定是一个合法的窗口，求最大窗口长度
            res = std::max(res, right - left);
        }
        return res;
    }
};