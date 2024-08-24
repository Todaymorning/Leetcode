// https://leetcode.cn/problems/container-with-most-water/description/?envType=study-plan-v2&envId=top-100-liked
// 11. 盛最多水的容器
// 已解答
// 中等
// 相关标签
// 相关企业
// 提示
// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
// 返回容器可以储存的最大水量。
// 说明：你不能倾斜容器。

// 示例 1：
// 输入：[1,8,6,2,5,4,8,3,7]
// 输出：49 
// 解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

// 示例 2：
// 输入：height = [1,1]
// 输出：1

// 提示：
// n == height.length
// 2 <= n <= 105
// 0 <= height[i] <= 104


#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    int maxArea(vector<int>& height) {

    }
};


// 双指针从两端到中间收缩，总是收缩最小的边
// 高度较小的那条边收缩原因：在最小高度确定的情况下收缩意味着面积有变小的趋势
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int sum = 0;
        while(left < right) {
            int cur = (right - left) * std::min(height[left], height[right]);
            if(cur > sum) sum = cur;
            if(height[left] < height[right]) left++;
            else right--;
        }
        return sum;
    }
};