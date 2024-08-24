// https://leetcode.cn/problems/subarray-sum-equals-k/description/?envType=study-plan-v2&envId=top-100-liked
// 560. 和为 K 的子数组
// 尝试过
// 中等
// 相关标签
// 相关企业
// 提示
// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。

// 子数组是数组中元素的连续非空序列。

// 示例 1：
// 输入：nums = [1,1,1], k = 2
// 输出：2

// 示例 2：
// 输入：nums = [1,2,3], k = 3
// 输出：2

// 提示：
// 1 <= nums.length <= 2 * 104
// -1000 <= nums[i] <= 1000
// -107 <= k <= 107

#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {

    }
};

// 枚举
// 遍历定出结尾，然后往前加
// 超时
class Solution_G1_M1 {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        for (int start = 0; start < nums.size(); ++start) {
            int sum = 0;
            for (int end = start; end >= 0; --end) {
                sum += nums[end];
                if (sum == k) {
                    count++;
                }
            }
        }
        return count;
    }
};



// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        // 前缀和数组
        vector<int> preSum(n + 1, 0);
        // 前缀和到该前缀和出现次数的映射，方便快速查找所需的前缀和
        unordered_map<int, int> count;
        count[0] = 1;
        // 记录和为 k 的子数组个数
        int res = 0;

        // 计算 nums 的前缀和
        for (int i = 1; i <= n; i++) {
            preSum[i] = preSum[i - 1] + nums[i - 1];
            // 如果之前存在值为 need 的前缀和
            // 说明存在以 nums[i-1] 结尾的子数组的和为 k
            int need = preSum[i] - k;
            if (count.find(need) != count.end()) {
                res += count[need];
            }
            // 将当前前缀和存入哈希表
            count[preSum[i]]++;
        }
        return res;
    }
};



// 12:16--12:41
class Solution_L1_M2 {
public:
    int subarraySum(vector<int>& nums, int k) {
        vector<int> preSum(nums.size() + 1, 0);
        for(int i=0; i<nums.size(); i++) {
            preSum[i+1] = nums[i] + preSum[i];
        }
        int count = 0;
        unordered_map<int, int> mp;
        for(int i=0; i<preSum.size(); i++) {
            // 先找 need = preSum[i] - k;
            if(mp.find(preSum[i] - k) != mp.end()) {
                count += mp[preSum[i] - k];
            }
            // 后统计
            if(mp.find(preSum[i]) == mp.end()) {
                mp.insert({preSum[i], 1});
            }
            else {
                mp[preSum[i]]++;
            }
        }
        return count;
    }
};