// https://leetcode.cn/problems/majority-element/description/?envType=study-plan-v2&envId=top-100-liked
// 169. 多数元素
// 已解答
// 简单
// 相关标签
// 相关企业
// 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。

 

// 示例 1：

// 输入：nums = [3,2,3]
// 输出：3
// 示例 2：

// 输入：nums = [2,2,1,1,1,2,2]
// 输出：2
 

// 提示：
// n == nums.length
// 1 <= n <= 5 * 104
// -109 <= nums[i] <= 109
 

// 进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。

#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;


class Solution {
public:
    int majorityElement(vector<int>& nums) {

    }
};


// hash
class Solution_M1 {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> mp;
        for(auto n : nums) {
            mp[n]++;
        }
        int n = nums.size() / 2;
        for(auto p : mp) {
            if(p.second > n) return p.first;
        }
        return -1;
    }
};


// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

// 目标值看作 1， 其他看作-1
class Solution_L1_copy {
public:
    int majorityElement(vector<int>& nums) {
        // 我们想寻找的那个众数
        int target = 0;
        // 计数器（类比带电粒子例子中的带电性）
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (count == 0) {
                // 当计数器为 0 时，假设 nums[i] 就是众数
                target = nums[i];
                // 众数出现了一次
                count = 1;
            } else if (nums[i] == target) {
                // 如果遇到的是目标众数，计数器累加
                count++;
            } else {
                // 如果遇到的不是目标众数，计数器递减
                count--;
            }
        }
        // 回想带电粒子的例子
        // 此时的 count 必然大于 0，此时的 target 必然就是目标众数
        return target;
    }
};


// sort
// 如果将数组 nums 中的所有元素按照单调递增或单调递减的顺序排序，那么下标为 n/2 的元素（下标从 0 开始）一定是众数。
// 链接：https://leetcode.cn/problems/majority-element/solutions/146074/duo-shu-yuan-su-by-leetcode-solution/
class Solution_G2_copy {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};



class Solution_G3_copy {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = INT_MIN;
        int count = 0;
        for(int num : nums) {
            if(num == candidate) {
                count++;
            }
            else if(--count < 0) {
                candidate = num;
                count = 1;
            }
        }
        return candidate;
    }
};
