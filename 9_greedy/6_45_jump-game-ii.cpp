// 45. 跳跃游戏 II
// 中等
// 给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。
// 每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:
// 0 <= j <= nums[i] 
// i + j < n
// 返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。

// 示例 1:
// 输入: nums = [2,3,1,1,4]
// 输出: 2
// 解释: 跳到最后一个位置的最小跳跃数是 2。
//      从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。

// 示例 2:
// 输入: nums = [2,3,0,1,4]
// 输出: 2

// 提示:
// 1 <= nums.length <= 10^4
// 0 <= nums[i] <= 1000
// 题目保证可以到达 nums[n-1]

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int jump(vector<int>& nums) {

    }
};


// 10:07--10:22--10:41
// 看了 D1 的思路
// 时间复杂度: O (n)
// 空间复杂度: O (1)
class Solution_D1_M1 {
public:
    int jump(vector<int>& nums) {
        if(nums.size() < 2) return 0;
        int steps = 0;
        int cur_cover = 0;
        int cover = 0;
        int temp;
        // 当前步能跳到的范围[cover(steps), cover(steps+1)]，i遍历这个范围，找到下一步能到达的最大值后更新
        for(int i=0; i<nums.size(); i++) {
            temp = nums[i] + i;
            if(temp > cur_cover) cur_cover = temp;  // 更新下一步中能cover的最大值
            if(i == cover && cur_cover > cover) {   // 遍历前一步能cover的区域后更新下一步的cover
                cover = cur_cover;
                steps++;
                if(cover >= nums.size() - 1) break;
            }
        }
        return steps;
    }
};


// 时间复杂度: O (n)
// 空间复杂度: O (1)
// 针对于方法一的特殊情况，可以统一处理，即：移动下标只要遇到当前覆盖最远距离的下标，直接步数加一，不考虑是不是终点的情况。
class Solution_D2 {
public:
    int jump(vector<int>& nums) {
        // if(nums.size() < 2) return 0;    // ***
        int steps = 0;
        int cur_cover = 0;
        int cover = 0;
        int temp;
        for(int i=0; i<nums.size() - 1; i++) {   // ***
            temp = nums[i] + i;
            if(temp > cur_cover) cur_cover = temp;
            if(i == cover && cur_cover > cover) {
                cover = cur_cover;
                steps++;
                // if(cover >= nums.size() - 1) break;  ***
            }
        }
        return steps;
    }
};




//*****************************************************************************************************************************
// 2024年5月17日
class Solution {
public:
    int jump(vector<int>& nums) {
        int cur_cover = 0;
        int next_cover = 0;
        int steps = 0;
        for(int i=0; i<nums.size() - 1; i++) {  // *** size - 1
            next_cover = std::max(next_cover, nums[i] + i);
            if(i == cur_cover) {
                steps++;
                cur_cover = next_cover;
            }
        }
        return steps;
    }
};