// 718. 最长重复子数组
// 中等
// 给两个整数数组 nums1 和 nums2 ，返回 两个数组中 公共的 、长度最长的子数组的长度 。

// 示例 1：
// 输入：nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
// 输出：3
// 解释：长度最长的公共子数组是 [3,2,1] 。

// 示例 2：
// 输入：nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
// 输出：5

// 提示：
// 1 <= nums1.length, nums2.length <= 1000
// 0 <= nums1[i], nums2[i] <= 100


#include<iostream>
#include<vector>
using std::vector;
using std::max;



class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {

    }
};


// 16:53--17:01(不会)--17:20(看了 D1 的 dp[i][j] 的定义后写的)
// 确定 dp 数组（dp table）以及下标的含义
// dp [i][j] ：以下标 i - 1 为结尾的 A，和以下标 j - 1 为结尾的 B，最长重复子数组长度为 dp [i][j]。
//  （特别注意： “以下标 i - 1 为结尾的 A” 标明一定是 以 A [i-1] 为结尾的字符串 ）
// 时间复杂度：O (n × m)，n 为 A 长度，m 为 B 长度
// 空间复杂度：O (n × m)
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int size1 = nums1.size();
        int size2 = nums2.size();
        vector<vector<int>> dp(size1+1, vector<int>(size2+1, 0));
        int result = 0;
        for(int i=1; i<=size1; i++) {
            for(int j=1; j<=size2; j++) {
                if(nums1[i-1] == nums2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;   // 对角线的数字加一
                if(dp[i][j] > result) result = dp[i][j];
            }
        }
        return result;
    }
};

// 17:20--17:32
// 滚动数组，倒序遍历，不相等时置零
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int size1 = nums1.size();
        int size2 = nums2.size();
        if(size1 == 0 || size2 == 0) return 0;
        vector<int> dp(size2 + 1, 0);
        int result = 0;
        for(int i=1; i<=size1; i++) {
            for(int j=size2; j>=1; j--) {   // 跟二维数组中的左上方有关，及滚动数组中前一个索引的数有关，因此 j 倒序
                if(nums1[i-1] == nums2[j-1]) {
                    dp[j] = dp[j-1] + 1;
                }
                else {
                    dp[j] = 0;  // 不相等时为0，相当于二维数组中的初始化    // ***
                }
                if(dp[j] > result) result = dp[j];
            }
        }
        return result;
    }
};