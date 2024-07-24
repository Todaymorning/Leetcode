// 27. 移除元素
// https://leetcode.cn/problems/remove-element/description/
// labuladong 题解
// 简单

// 提示
// 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
// 不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
// 元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

// 说明:
// 为什么返回数值是整数，但输出的答案是数组呢？
// 请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

// 你可以想象内部操作如下:
// // nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
// int len = removeElement(nums, val);
// // 在函数里修改输入数组对于调用者是可见的。
// // 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
// for (int i = 0; i < len; i++) {
//     print(nums[i]);
// }

// 示例 1：
// 输入：nums = [3,2,2,3], val = 3
// 输出：2, nums = [2,2]
// 解释：函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。你不需要考虑数组中超出新长度后面的元素。
// 例如，函数返回的新长度为 2 ，而 nums = [2,2,3,3] 或 nums = [2,2,0,0]，也会被视作正确答案。

// 示例 2：
// 输入：nums = [0,1,2,2,3,0,4,2], val = 2
// 输出：5, nums = [0,1,3,0,4]
// 解释：函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。注意这五个元素可为任意顺序。
// 你不需要考虑数组中超出新长度后面的元素。

// 提示：
// 0 <= nums.length <= 100
// 0 <= nums[i] <= 50
// 0 <= val <= 100




#include <iostream>
#include <vector>
using namespace std;

// 27.移除元素
// 给你一个数组 nums 和一个值va1，你需要原地移除所有数值等于val的元素，并返回移除后数组的新长度。
// 不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并原地修改输入数组。
// 元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。


class Solution {
public:
    int removeElement(vector<int>& nums, int val) {

    }
};


// 暴力算法:
int removeElement1(vector<int> & nums, int val)
{
    int size = nums.size();
    for(int i=0; i<size; i++)
    {
        if(nums[i] == val)  // 需要移除的元素
        {
            for(int j=i; j<size-1; j++)
            {
                nums[j] = nums[j+1];
            }
        }
        i--;    // 下标 -1
        size--; // 长度 -1
    }
    return size;
}

// 快慢指针：你的指针何必是指针
// 慢指针指向修改后应有的下标，快指针顺序指向下一个
int removeElement2(vector<int> & nums, int val)
{
    int slow = 0;
    int size = nums.size();
    for(int fast=0; fast<size; fast++)  // fast 遍历
    {
        if(nums[fast] != val)
        {
            nums[slow++] = nums[fast];  // slow 填一个再自增
        }
    }
    return slow;
}

// 相向双指针：基于元素顺序可以改变的题目描述改变了元素相对位置，确保了移动最少元素
int removeElement3(vector<int> & nums, int val)
{
    int left = 0;
    int right = nums.size() -1;
    while(left <= right)
    {
        // 找左边等于 val 的元素
        while(left <= right && nums[left] != val)
        {
            left++;
        }
        // 找右边不等于 val 的元素
        while(left <= right && nums[right] == val)
        {
            right--;
        }
        // 用右边覆盖左边
        if(left < right)
        {
            nums[left++] = nums[right--];   // ***, 一定要 ++ --，方便比较未比较的元素
        }
    }
    return left;   // left 指向最后一个元素
}

// 双指针优化
// 补左边，右边不判断
int removeElement4(vector<int> & nums, int val)
{
    int left = 0;
    int right = nums.size()-1;
    while(left <= right)
    {
        if(nums[left] == val)
        {
            nums[left] = nums[right];
            right--;
        }
        else
            left++;
    }
    return left;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 16:37--16:50
// 双指针
// 不改变元素的相对位置
class Solution_S2_M1 {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for(int fast=0; fast<nums.size(); fast++) {
            if(nums[fast] != val) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;    // 一直指向最后一个元素
    }
};


/**
* 相向双指针方法，基于元素顺序可以改变的题目描述改变了元素相对位置，确保了移动最少元素
* 时间复杂度：O(n)
* 空间复杂度：O(1)
*/
class Solution_D2_copy {
public:
    int removeElement(vector<int>& nums, int val) {
        int leftIndex = 0;
        int rightIndex = nums.size() - 1;
        while (leftIndex <= rightIndex) {
            // 找左边等于val的元素
            while (leftIndex <= rightIndex && nums[leftIndex] != val){
                ++leftIndex;
            }
            // 找右边不等于val的元素
            while (leftIndex <= rightIndex && nums[rightIndex] == val) {
                -- rightIndex;
            }
            // 将右边不等于val的元素覆盖左边等于val的元素
            if (leftIndex < rightIndex) {
                nums[leftIndex++] = nums[rightIndex--];
            }
        }
        return leftIndex;   // leftIndex一定指向了最终数组末尾的下一个元素
    }
};