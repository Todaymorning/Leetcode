// https://leetcode.cn/problems/sort-an-array/
// 912.排序数组


#include <iostream>
#include <vector>   // std::vector
#include <ctime>    // time
using std::vector;
using std::swap;


class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {

    }
};


// 14:53--15:06
class Solution1 {
    int position(vector<int>& nums, int left, int right) {
        int key = nums[right];
        int mid = left;
        for(int j=left; j<right; j++) {
            if(nums[j] < key) {
                swap(nums[j], nums[mid++]);
            }
        }
        swap(nums[mid], nums[right]);
        return mid;
    }
    // [left, right]
    void quick_sort(vector<int>& nums, int left, int right) {
        if(left < right) {
            int mid = position(nums, left, right);
            quick_sort(nums, left, mid-1);
            quick_sort(nums, mid + 1, right);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size() - 1);
        return nums;
    }
};

// 加点随机
// 14:53--15:06--15:18
class Solution2 {
    int position(vector<int>& nums, int left, int right) {
        int idx = rand()%(right - left + 1) + left;
        int key = nums[idx];
        swap(nums[idx], nums[right]);
        int mid = left;
        for(int j=left; j<right; j++) {
            if(nums[j] < key) {
                swap(nums[j], nums[mid++]);
            }
        }
        swap(nums[mid], nums[right]);
        return mid;
    }
    // [left, right]
    void quick_sort(vector<int>& nums, int left, int right) {
        if(left < right) {
            int mid = position(nums, left, right);
            quick_sort(nums, left, mid-1);
            quick_sort(nums, mid + 1, right);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size() - 1);
        return nums;
    }
};


// 三数取中
// 14:53--15:06--15:18
class Solution3 {
    int position(vector<int>& nums, int left, int right) {
        // 让 right 变为中间值
        select(nums, left, right);
        int key = nums[right];
        int mid = left;
        for(int j=left; j<right; j++) {
            if(nums[j] < key) {
                swap(nums[j], nums[mid++]);
            }
        }
        swap(nums[mid], nums[right]);
        return mid;
    }
    // [left, right]
    void quick_sort(vector<int>& nums, int left, int right) {
        if(left < right) {
            int mid = position(nums, left, right);
            quick_sort(nums, left, mid-1);
            quick_sort(nums, mid + 1, right);
        }
    }
    void select(vector<int>& nums, int left, int right) {
        // 目标 nums[right] 存放中间值
        int mid = left + (right - left) / 2;
        if(nums[mid] < nums[left]) swap(nums[left], nums[mid]); // nums[mid] >= nums[left];
        if(nums[mid] < nums[right]) swap(nums[mid], nums[right]);   // nums[mid] >= nums[right];
        if(nums[left] > nums[right]) swap(nums[left], nums[right]); // nums[right] >= nums[left] 是中间值
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size() - 1);
        return nums;
    }
};


class Solution3 {

    void quick_sort(vector<int>& nums, int left, int right) {
        if(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] < nums[left]) swap(nums[left], nums[mid]); // nums[mid] >= nums[left];
            if(nums[mid] < nums[right]) swap(nums[mid], nums[right]);   // nums[mid] >= nums[right];
            if(nums[left] > nums[right]) swap(nums[left], nums[right]); // nums[right] >= nums[left] 是中间值


            int key = nums[right];
            int i = left;
            for(int j=left; j<right; j++) {
                if(nums[j] < key) {
                    swap(nums[j], nums[i++]);
                }
            }
            swap(nums[i], nums[right]);


            quick_sort(nums, left, i-1);
            quick_sort(nums, i + 1, right);
        }
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size() - 1);
        return nums;
    }
};





// 16:33
class Solution {
    int position(vector<int>& nums, int left, int right) {
        
    }
    void quick_sort(vector<int>& nums, int left, int right) {
        if(left < right) {
            int mid = position(nums, left, right);
            quick_sort(nums, left, mid - 1);
            quick_sort(nums, mid + 1, right);
        }
    }
    void choose(vector<int>& nums, int left, int right) {
        int mid = left + (right - left) / 2;
        // if(nums[left] < )
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quick_sort(nums, 0, nums.size() - 1);
        return nums;
    }
};