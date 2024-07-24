// 377. 组合总和 Ⅳ
// 中等
// 给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。
// 题目数据保证答案符合 32 位整数范围。

// 示例 1：
// 输入：nums = [1,2,3], target = 4
// 输出：7
// 解释：
// 所有可能的组合为：
// (1, 1, 1, 1)
// (1, 1, 2)
// (1, 2, 1)
// (1, 3)
// (2, 1, 1)
// (2, 2)
// (3, 1)
// 请注意，顺序不同的序列被视作不同的组合。

// 示例 2：
// 输入：nums = [9], target = 3
// 输出：0

// 提示：
// 1 <= nums.length <= 200
// 1 <= nums[i] <= 1000
// nums 中的所有元素 互不相同
// 1 <= target <= 1000

// 进阶：如果给定的数组中含有负数会发生什么？问题会产生何种变化？如果允许负数出现，需要向题目中添加哪些限制条件？


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {

    }
};

// 17:52--17:56
// 1 确定 dp 数组以及下标的含义
// 2 确定递推公式
// 3 dp 数组如何初始化
// 4 确定遍历顺序
// 5 举例来推导 dp 数组
// 如果本题要把排列都列出来的话，只能使用回溯算法爆搜。
// dp [i]: 凑成目标正整数为 i 的排列个数为 dp [i]
// dp [i]（考虑 nums [j]）可以由 dp [i - nums [j]]（不考虑 nums [j]） 推导出来。
// 如果求组合数就是外层 for 循环遍历物品，内层 for 遍历背包。
// 如果求排列数就是外层 for 遍历背包，内层 for 循环遍历物品。
// 时间复杂度: O (target * m)，其中 m 为 nums 的长度
// 空间复杂度: O (target)
// C++ 测试用例有两个数相加超过 int 的数据，所以需要在 if 里加上 dp [i] < INT_MAX - dp [i - num]。
class Solution_M1_D1 {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int m = nums.size();
        vector<int> dp(target + 1, 0);  // 或者这里改为 double
        dp[0] = 1;
        for(int j=1; j<=target; j++) {  // 遍历背包
            for(int i=0; i<m; i++) {    // 遍历物品
                if(j >= nums[i] && dp[j] < INT_MAX - dp[j - nums[i]]) { // 加了个限制，只是因为测试样例的原因
                    dp[j] = dp[j] + dp[j - nums[i]];
                }
            }
        }
        
        return dp.back();
    }
};

//17:56--18:00--18:06(错误)
// 输入
// nums =
// [9]
// target =
// 3
// 输出
// 1
// 预期结果
// 0
class Solution_M2 {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int m = nums.size();
        vector<vector<int>> dp(m + 1, vector<int>(target + 1, 0));
        // 初始化第 0 列
        for(int i=0; i<=m; i++) {
            dp[i][0] = 1;
        }
        for(int j=1; j<=target; j++) {  // 遍历背包
            for(int i=1; i<=m; i++) {   // 遍历物品
                if(j >= nums[i-1]) {
                    dp[i][j] = dp[i-1][j] + dp[m][j - nums[i-1]];   // 先遍历背包，再遍历物品，进入下一个背包空间（j+1）时，j的最后一行才是j的最终答案
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[m][target];
    }
};