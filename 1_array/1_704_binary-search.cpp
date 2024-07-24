// 704. 二分查找
// https://leetcode.cn/problems/binary-search/description/
// labuladong 题解思路
// 简单
// 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，
// 如果目标值存在返回下标，否则返回 -1。

// 示例 1:
// 输入: nums = [-1,0,3,5,9,12], target = 9
// 输出: 4
// 解释: 9 出现在 nums 中并且下标为 4

// 示例 2:
// 输入: nums = [-1,0,3,5,9,12], target = 2
// 输出: -1
// 解释: 2 不存在 nums 中因此返回 -1

// 提示：
// 你可以假设 nums 中的所有元素是不重复的。
// n 将在 [1, 10000] 之间。
// nums 的每个元素都将在 [-9999, 9999] 之间。

#include <iostream>
#include <vector>
using namespace std;


// 704. 二分查找
// 给定一个n个元素有序的（升序）整型数组 nums 和一个目标值 target
// 写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回-1。
// 提示：
// · 你可以假设 nums 中的所有元素是不重复的。
// · n将在 [1，10000] 之间。
// · nums 的每个元素都将在 [-9999，9999] 之间。
// 
// 以边界定区间(while 条件是否有等号)
// 以无 middle 定下次左右
// 如果 middle 重复使用的话，可能会陷入死循环

// 写法一:
// [left, right] ————> [left, middle-1]、[middle+1, right]
int search(vector<int> & nums, int target)
{
    int left = 0;
    int right = nums.size()-1;      // [left, right]
    int middle;
    if(target < nums[left] || target > nums[right])
        return -1;
    while(left <= right)    // left = right 时 [left, right] 有效，也可不加 =
    {
        // middle = (left+right)/2;    // ***   左侧中点(偶数时)
        // middle = left + (right - left)/2;    // 防止下标溢出
        middle = left + ((right-left) >> 1);  // 防止下标溢出，位运算求中点
        if(nums[middle] > target)
        {
            right = middle - 1;     // 大了看前半部分，[left, middle-1]
        }
        else if(nums[middle] < target)
        {
            left = middle + 1;      // 小了看后半部分，[middle+1, right]
        }
        else    // nums[middle] == target
            return middle;
    }
    return -1;
}

// 写法二：
// [left, right) ————>
int search2(vector<int> nums, int target)
{
    int left = 0;
    int right = nums.size();    // [left, right)
    int middle;
    if(target < nums[left] || target > nums[right-1])   // 注意下标
        return -1;
    while(left < right)         // left = right [left, right) 无意义
    {
        middle = left + (right-left)/2;   // 右侧中点
        // middle = left + ((right - left) >> 1);   // 位运算； 防止溢出
        if(nums[middle] > target)
        {
            right = middle;         // 大了看前半部分，[left, middle)
        }
        else if(nums[middle] < target)
        {
            left = middle + 1;      // 小了看后半部分，[middle+1, right)
        }
        else
            return middle;
    }
    return -1;
}

// 错误示例：更新区间时重复使用之前使用的 middle，陷入死循环
#if 0
int main()
{
    vector<int> nums = {-1,0,3,5,9,12};
    int target = 2;
    int left = 0;
    int right = nums.size();
    int middle;
    while(left < right)
    {
        middle = left + ((right - left) >> 1);
        cout << "[ " << left << ", " << right << " ]" << "  middle: " << middle << endl;
        if(nums[middle] > target)
        {
            right = middle;
        }
        else if(nums[middle] < target)
        {
            left = middle;      // 小了看后半部分，[middle+1, right)，但我这里没有加
        }
        else
            cout << "found in: " << middle << endl;
    }
    cout << "not found";
    return 0;
}
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 暴力搜索
class Solution_S2_M1 {
public:
    int search(vector<int>& nums, int target) {
        // 14:59
        int result = -1;
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] == target) {
                result = i;
            }
            if(nums[i] > target) break;
        }
        return result;
    }
};
