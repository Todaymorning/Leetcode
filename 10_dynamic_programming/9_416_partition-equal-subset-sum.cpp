// 416. 分割等和子集
// labuladong 题解思路
// 中等
// 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

// 示例 1：
// 输入：nums = [1,5,11,5]
// 输出：true
// 解释：数组可以分割成 [1, 5, 5] 和 [11] 。

// 示例 2：
// 输入：nums = [1,2,3,5]
// 输出：false
// 解释：数组不能分割成两个元素和相等的子集。

// 提示：
// 1 <= nums.length <= 200
// 1 <= nums[i] <= 100

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    bool canPartition(vector<int>& nums) {

    }
};


// 11:03--11:11(错误)--11:30(调试，没找到原因)--11::33(看了 L，int 改为 bool)
class Solution_M1_L1 {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(int n:nums) sum += n;
        if(sum % 2 == 1) return false;
        sum /= 2;
        vector<vector<bool>> dp(nums.size() + 1, vector<bool>(sum + 1, 0)); // ***
        dp[0][0] = true;
        for(int i=1; i<=nums.size(); i++) {
            for(int j=0; j<=sum; j++) {
                if(j >= nums[i-1]) {
                    dp[i][j] = dp[i-1][j] + dp[i-1][j - nums[i-1]];
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
            }
            if(dp[i][sum] != 0) return true;
        }
        if(dp[nums.size()][sum]) return true;
        return false;
    }
};

// 正整数，大于等于 1
// 第 0 列 为 true
// dp[i-1][...] 会访问 i-1行，因此 i 从 1 开始
// nums[i] >= 1，因此 j 从 1 开始
// dp[i-1][j - nums[i-1]]，j == nums[i-1] 时会访问第 0 列的元素，需要正确初始化
// dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]]：
// 当 j == nums[i-1] 时，dp[i - 1][j]可能为 false，而 dp[i][j] 应该是 true，因此第 0 列为 true
class Solution_L1_copy {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) sum += num;
        // 和为奇数时，不可能划分成两个和相等的集合
        if (sum % 2 != 0) return false;
        int n = nums.size();
        sum = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
        // base case
        for (int i = 0; i <= n; i++)    // 第 0 列为 true
            dp[i][0] = true;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= sum; j++) {
                if (j - nums[i - 1] < 0) { 
                    // 背包容量不足，不能装入第 i 个物品
                    dp[i][j] = dp[i - 1][j];
                } else { 
                    // 装入或不装入背包
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
                }
            }
        }
        return dp[n][sum];
    }
};


// 11:40--11:47
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(int n:nums) sum += n;
        if(sum % 2 == 1) return false;
        sum /= 2;
        int m = nums.size();
        vector<bool> dp(sum + 1, false);
        dp[0] = true;
        for(int i=1; i<=m; i++) {
            for(int j=sum; j>=nums[i-1]; j--) {
                dp[j] = dp[j] || dp[j - nums[i-1]];
            }
            if(dp[sum] == true) return true;
        }
        return dp[sum];
    }
};
