// https://leetcode.cn/problems/jump-game/
// 55. 跳跃游戏
// labuladong 题解
// 思路
// 已解答
// 中等
// 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
// 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。

// 示例 1：
// 输入：nums = [2,3,1,1,4]
// 输出：true
// 解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。

// 示例 2：
// 输入：nums = [3,2,1,0,4]
// 输出：false
// 解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。

// 提示：
// 1 <= nums.length <= 10^4
// 0 <= nums[i] <= 10^5


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    bool canJump(vector<int>& nums) {

    }
};


// 15:11--15:21(题目理解错误)
// 超出数组的索引也算对，不用刚好等于
// 是最大跳跃的长度，也可以不用跳得那么长
// 输入[0]，应该输出true
// 输入 nums =[2,5,0,0]
// 输出 false
// 预期结果 true
#if 0
class Solution_M1 {
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size() - 1;
        int i;
        for(i=0; i<=size;) {
            if(nums[i] == 0) {
                if(i >= size) return true;
                return false;
            }
            i += nums[i];
        }
        if(i >= size) return true;
        return false;
    }
};
#endif


// 看完 D1 的思路后写出，中间遇到一个错误
// i 每次移动只能在 cover 的范围内移动，每移动一个元素，cover 得到该元素数值（新的覆盖范围）的补充，让 i 继续移动下去。
// 而 cover 每次只取 max (该元素数值补充后的范围，cover 本身范围)。
// 遇到的错误
// 输入 nums =[0,1]
// 输出 true
// 预期结果 false
class Solution_D1_M1 {
public:
    bool canJump(vector<int>& nums) {
        int cover = 1;  // 可覆盖的个数
        int temp;
        for(int i=0; i<nums.size(); i++) {
            if(i >= cover) break;           // 确保在可覆盖的范围内更新可覆盖范围
            temp = i + nums[i] + 1;         // ***
            if(temp > cover) cover = temp;  // 更新最大覆盖范围
            if(cover >= nums.size()) break; // 可以覆盖全部
        }
        if(cover >= nums.size()) return true;
        return false;
    }
};


//*****************************************************************************************************************************
// 时间复杂度: O (n)
// 空间复杂度: O (1)
// 维护一个可覆盖区域
class Solution_D1 {
public:
    bool canJump(vector<int>& nums) {
        int cover = 0;
        int temp;
        for(int i=0; i<=cover; i++) {
            temp = i + nums[i];
            if(temp > cover) cover = temp;  // 更新 cover
            if(cover >= nums.size() - 1) return true;
        }
        return false;
    }
};


class Solution_G1 {
public:
    bool canJump(vector<int>& nums) {
        int cover = 0;
        for(int i=0; i<nums.size(); i++) {
            if(i <= cover) {
                cover = std::max(cover, nums[i] + i);
                if(cover >= nums.size() - 1) return true;
            }
        }
        return false;
    }
};


//*****************************************************************************************************************************
// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1_copy {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int farthest = 0;
        for (int i = 0; i < n - 1; i++) {
            // 不断计算能跳到的最远距离
            farthest = std::max(farthest, i + nums[i]);
            // 可能碰到了 0，卡住跳不动了
            if (farthest <= i) {
                return false;
            }
        }
        return farthest >= n - 1;
    }
};
// 详细解析参见：
// https://labuladong.online/algo/slug.html?slug=jump-game





// 2024年5月13日
// 16:37--16:44
// 遇到 [0] 错误
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size();
        if(size == 0) return true;
        int right = 0;
        int temp;
        for(int i=0; i<=right; i++) {
            temp = i + nums[i];
            if(temp > right) right = temp;
            if(right >= size-1) return true;
        }
        return false;
    }
};