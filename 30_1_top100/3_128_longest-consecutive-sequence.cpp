// https://leetcode.cn/problems/longest-consecutive-sequence/?envType=study-plan-v2&envId=top-100-liked
// 128. 最长连续序列
// 已解答
// 中等
// 相关标签
// 相关企业
// 给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
// 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

// 示例 1：
// 输入：nums = [100,4,200,1,3,2]
// 输出：4
// 解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。

// 示例 2：
// 输入：nums = [0,3,7,2,5,8,4,6,0,1]
// 输出：9

// 提示：
// 0 <= nums.length <= 105
// -109 <= nums[i] <= 109



#include<iostream>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;


class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

    }
};

// 2024年7月23日
// 16点43分
class Solution_G1_M1 {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() < 2) return nums.size();
        unordered_set<int> st;
        for(auto num : nums) {
            st.insert(num);
        }
        int res = 1;
        for(int i=0; i<nums.size(); i++) {
            int num = nums[i];
            // 不是序列头，不用接着往下走       // ***
            if(st.find(num - 1) != st.end()) {
                continue;
            }
            // 是序列头
            while(st.find(num + 1) != st.end()) {
                num++;
                int cur = num - nums[i] + 1;
                res = res > cur ? res : cur;    // 不推荐，看官方
            }
        }
        return res;
    }
};


class Solution_G1_copy {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;           
    }
};




// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1_copy {
public:
    int longestConsecutive(vector<int>& nums) {
        // 转化成哈希集合，方便快速查找是否存在某个元素
        unordered_set<int> set(nums.begin(), nums.end());

        int res = 0;

        for (int num : set) {
            if (set.find(num - 1) != set.end()) {
                // num 不是连续子序列的第一个，跳过
                continue;
            }
            // num 是连续子序列的第一个，开始向上计算连续子序列的长度
            int curNum = num;
            int curLen = 1;

            while (set.find(curNum + 1) != set.end()) {
                curNum += 1;
                curLen += 1;
            }
            // 更新最长连续序列的长度
            res = max(res, curLen);
        }

        return res;
    }
};