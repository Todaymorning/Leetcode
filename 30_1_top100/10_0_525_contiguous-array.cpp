// https://leetcode.cn/problems/contiguous-array
// 525. 连续数组
// 已解答
// 中等
// 相关标签
// 相关企业
// 给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。

// 示例 1:
// 输入: nums = [0,1]
// 输出: 2
// 说明: [0, 1] 是具有相同数量 0 和 1 的最长连续子数组。

// 示例 2:
// 输入: nums = [0,1,0]
// 输出: 2
// 说明: [0, 1] (或 [1, 0]) 是具有相同数量0和1的最长连续子数组。

// 提示：
// 1 <= nums.length <= 105
// nums[i] 不是 0 就是 1




#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {

    }
};



// 基本思路:
// 首先，我们做一个等价，题目让你找 0 和 1 数量相同的最长子数组，
// 如果我们把 0 视作 -1，就把题目转变成了：寻找和为 0 的最长子数组。
// 涉及到和为 xxx 的子数组，就是要考察 前缀和技巧 和哈希表的结合使用了。
// 求和为 0 的最长子数组，相当于让你去 preSum 数组中找 i, j，
// 使得 preSum[i] - preSum[j] == 0，其中 i > j 且 i - j 要尽可能大。
// 那么我们用一个哈希表 valToIndex 存储前缀和到索引的映射，
// 给定任意 preSum[i]，我们都能通过 valToIndex 快速判断是否存在 j，
// 使得 preSum[i] - preSum[j] == 0。
// 值得一提的是，我给的解法中 preSum 数组可以进一步简化成变量，这个优化可以留给你来做。


// 可以考察 和为target的存在性，最长、最短子数组
// +++ 寻找和为 target 的最长子数组 (数组元素可正可负) +++
// +++ 寻找和为 target 的最短子数组 (数组元素可正可负) +++



// 前缀和 + hash表
// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。
class Solution_L1_copy {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> preSum(n + 1, 0);
        // 计算 nums 的前缀和
        for (int i = 0; i < n; i++) {
            preSum[i + 1] = preSum[i] + (nums[i] == 0 ? -1 : 1);
        }
        // 前缀和到索引的映射，方便快速查找所需的前缀和
        unordered_map<int, int> valToIndex;
        int res = 0;
        for (int i = 0; i < preSum.size(); i++) {
            // 如果这个前缀和还没有对应的索引，说明这个前缀和第一次出现，记录下来
            if (valToIndex.find(preSum[i]) == valToIndex.end()) {
                // 如果是求最短子数组的话需要记录最新出现的位置
                valToIndex[preSum[i]] = i;  // 保证只记录第一个，前缀和索引尽可能小
            } else {
                // 这个前缀和已经出现过了，则找到一个和为 0 的子数组
                res = max(res, i - valToIndex[preSum[i]]);
            }
            // 因为题目想找长度最大的子数组，所以前缀和索引应尽可能小
        }
        return res;
    }
};