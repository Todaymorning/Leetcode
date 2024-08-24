// https://leetcode.cn/problems/search-in-rotated-sorted-array
// 33. 搜索旋转排序数组
// 思路
// 中等
// 相关标签
// 相关企业
// 整数数组 nums 按升序排列，数组中的值 互不相同 。
// 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 
// [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
// 例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
// 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
// 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

// 示例 1：
// 输入：nums = [4,5,6,7,0,1,2], target = 0
// 输出：4

// 示例 2：
// 输入：nums = [4,5,6,7,0,1,2], target = 3
// 输出：-1

// 示例 3：
// 输入：nums = [1], target = 0
// 输出：-1

// 提示：
// 1 <= nums.length <= 5000
// -10^4 <= nums[i] <= 10^4
// nums 中的每个值都 独一无二
// 题目数据保证 nums 在预先未知的某个下标上进行了旋转
// -10^4 <= target <= 10^4

#include<iostream>
#include<vector>
using std::vector;


class Solution {
public:
    int search(vector<int>& nums, int target) {

    }
};


// 22:25--23:06--部分错误
// 输入
// nums =
// [1,2,3,4,5,6]
// target =
// 4
// 输出
// -1
// 预期结果
// 3
#if 0
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        if(size == 0) return -1;
        if(size == 1) return (nums[0] == target ? 0 : -1);
        int left = 0;
        int right = size - 1;
        int mid;
        while(left <= right) {  // *** 
            mid = left + (right - left) / 2;
            if(nums[left] == target) return left;
            if(nums[mid] == target) return mid;
            if(nums[right] == target) return right;

            if(nums[mid] > nums[left]) {    // k 在 mid 右边
                if(nums[left] > target) {   // 在右侧找
                    left = mid + 1;
                    right--;
                }
                else {                      // 在左侧找
                    right = mid - 1;
                    left++;
                }
            }
            else {  // k 在 mid 左边
                if(nums[right] < target) { // 在左侧找
                    right = mid - 1;
                    left++;
                }
                else {
                    left = mid + 1;
                    right--;
                }
            }
        }
        return -1;
    }
};
#endif


class Solution_L1_M1 {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        if(size == 0) return -1;
        if(size == 1) return nums[0] == target ? 0 : -1;
        int left = 0; 
        int right = size - 1;
        int mid;
        while(left <= right) {  // ***
            mid = left + (right - left) / 2;
            if(nums[left] == target) return left;
            if(nums[mid] == target) return mid;
            if(nums[right] == target) return right;
            if(nums[mid] > nums[right]) {
                // 断崖在mid右侧，[left, mid] 有序
                if(target > nums[left] && target < nums[mid]) {
                    right = mid - 1;
                    left++;
                }
                else {
                    left = mid + 1;
                    right--;
                }
            }
            else {
                // 断崖在mid左侧 [mid, right] 有序
                if(target > nums[mid] && target < nums[right]) {
                    left = mid + 1;
                    right--;
                }
                else {
                    right = mid - 1;
                    left++;
                }
            }
        }
        return -1;
    }
};




// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1_copy {
public:
    int search(vector<int>& nums, int target) {
        // 左右都闭的搜索区间
        int left = 0, right = nums.size() - 1;
        // 因为是闭区间，所以结束条件为 left > right
        while (left <= right) {
            int mid = left + (right - left) / 2;
            // 首先检查 nums[mid]，是否找到 target
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] >= nums[left]) {                          // ***
                // mid 落在断崖左边，此时 nums[left..mid] 有序
                if (target >= nums[left] && target < nums[mid]) {
                    // target 落在 [left..mid-1] 中
                    right = mid - 1;
                } else {
                    // target 落在 [mid+1..right] 中
                    left = mid + 1;
                }
            } else {
                // mid 落在断崖右边，此时 nums[mid..right] 有序
                if (target <= nums[right] && target > nums[mid]) {
                    // target 落在 [mid+1..right] 中
                    left = mid + 1;
                } else {
                    // target 落在 [left..mid-1] 中
                    right = mid - 1;
                }
            }
        }
        // while 结束还没找到，说明 target 不存在
        return -1;
    }
};

// 23:16
// left mid gap right
// left gap mid right
// 有序的判断
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // [left, right]
        int left = 0, right = nums.size()-1;
        while(left <= right) {
            int mid = left + (right - left)/2;
            if(nums[mid] == target) return mid;
            // 断崖在 mid 右边，[left, mid]有序
            if(nums[mid] >= nums[left]) {   // *** =
                if(target >= nums[left] && target < nums[mid]) {    // mid 已经比较过了
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else {
                // 断崖在 mid 左边 [mid, right]有序
                if(target <= nums[right] && target > nums[mid]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};