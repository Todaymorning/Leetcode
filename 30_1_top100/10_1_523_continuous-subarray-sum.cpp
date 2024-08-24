// https://leetcode.cn/problems/continuous-subarray-sum
// 523. 连续的子数组和
// 中等
// 相关标签
// 相关企业
// 给你一个整数数组 nums 和一个整数 k ，如果 nums 有一个 好的子数组 返回 true ，否则返回 false：

// 一个 好的子数组 是：

// 长度 至少为 2 ，且
// 子数组元素总和为 k 的倍数。
// 注意：

// 子数组 是数组中 连续 的部分。
// 如果存在一个整数 n ，令整数 x 符合 x = n * k ，则称 x 是 k 的一个倍数。0 始终 视为 k 的一个倍数。
 

// 示例 1：

// 输入：nums = [23,2,4,6,7], k = 6
// 输出：true
// 解释：[2,4] 是一个大小为 2 的子数组，并且和为 6 。
// 示例 2：

// 输入：nums = [23,2,6,4,7], k = 6
// 输出：true
// 解释：[23, 2, 6, 4, 7] 是大小为 5 的子数组，并且和为 42 。 
// 42 是 6 的倍数，因为 42 = 7 * 6 且 7 是一个整数。
// 示例 3：

// 输入：nums = [23,2,6,4,7], k = 13
// 输出：false
 

// 提示：

// 1 <= nums.length <= 105
// 0 <= nums[i] <= 109
// 0 <= sum(nums[i]) <= 231 - 1
// 1 <= k <= 231 - 1




#include <vector>
#include <unordered_map>
using namespace std;


class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {

    }
};

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        vector<int> preSum(nums.size() + 1, 0);
        // 计算前缀和
        for(int i=0; i<nums.size(); i++) {
            preSum[i+1] = nums[i] + preSum[i];
        }
        // 查找
        unordered_map<int, int> idx;
        for(int i=0; i<preSum.size(); i++) {
            // 存余数   ***
            int res = preSum[i] % k;
            if(idx.find(res) == idx.end()) {
                idx.insert({res, i});   // 需要最长，只记录第一个
            }
            else if(i - idx[res] >= 2) {    // 判断是否满足间距要求 ***
                return true;
            }
        }
        return false;
    }
};



// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        // 计算 nums 的前缀和
        vector<int> preSum(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            preSum[i] = preSum[i - 1] + nums[i - 1];
        }
        // 前缀和与 k 的余数到索引的映射，方便快速查找所需的前缀和
        unordered_map<int, int> valToIndex;
        for (int i = 0; i < preSum.size(); i++) {
            // 在哈希表中记录余数
            int val = preSum[i] % k;    
            // 如果这个余数还没有对应的索引，则记录下来
            if (!valToIndex.count(val)) {
                valToIndex[val] = i;
            }
            // 如果这个前缀和已经有对应的索引了，则什么都不做
            // 因为题目想找长度最大的子数组，所以前缀和索引应尽可能小
        }
        for (int i = 1; i < preSum.size(); i++) {
            // 计算 need，使得 (preSum[i] - need) % k == 0
            int need = preSum[i] % k;
            if (valToIndex.count(need)) {
                if (i - valToIndex[need] >= 2) {
                    // 这个子数组的长度至少为 2
                    return true;
                }
            }
        }
        return false;
    }
};