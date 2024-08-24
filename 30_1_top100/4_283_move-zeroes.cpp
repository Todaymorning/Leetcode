// https://leetcode.cn/problems/move-zeroes/description/?envType=study-plan-v2&envId=top-100-liked
// 283. 移动零
// 已解答
// 简单
// 相关标签
// 相关企业
// 提示
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
// 请注意 ，必须在不复制数组的情况下原地对数组进行操作。

// 示例 1:
// 输入: nums = [0,1,0,3,12]
// 输出: [1,3,12,0,0]

// 示例 2:
// 输入: nums = [0]
// 输出: [0]

// 提示:
// 1 <= nums.length <= 104
// -231 <= nums[i] <= 231 - 1

// 进阶：你能尽量减少完成的操作次数吗？


#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {

    }
};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(), left = 0, right = 0;
        while(right < n) {
            if(nums[right] != 0) {
                std::swap(nums[left], nums[right]);
                left++;
            }
            right++;
        }
    }
};



// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1_copy {
public:
    void moveZeroes(vector<int>& nums) {
        // 去除 nums 中的所有 0
        // 返回去除 0 之后的数组长度
        int p = removeElement(nums, 0);
        // 将 p 之后的所有元素赋值为 0
        for (; p < nums.size(); p++) {
            nums[p] = 0;
        }
    }

    // 双指针技巧，复用 [27. 移除元素] 的解法。
    int removeElement(vector<int>& nums, int val) {
        int fast = 0, slow = 0;
        while (fast < nums.size()) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        return slow;    // slow 指向不需要的位置
    }
};
// 详细解析参见：
// https://labuladong.online/algo/slug.html?slug=move-zeroes
