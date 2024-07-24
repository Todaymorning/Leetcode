// 90. 子集 II
// 中等
// 给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
// 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。

// 示例 1：
// 输入：nums = [1,2,2]
// 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]

// 示例 2：
// 输入：nums = [0]
// 输出：[[],[0]]
 
// 提示：
// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10

#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using std::unordered_set;
using std::vector;
using std::sort;
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {

    }
};


// 先排序再用idx去重
// 11:37--12:11
// 单个子集中可以有重复的元素，但两个子集的元素不可以完全相同
// 先排序，再用 idx 去重
// 本题也可以不使用 used 数组来去重，因为递归的时候下一个 idx 是 i+1 而不是 0。
// 如果要是全排列的话，每次要从 0 开始遍历，为了跳过已入栈的元素，需要使用 used。
class Solution_M1_D2 {
    vector<vector<int>> result;
    vector<int> track;
    void backtrack(vector<int>& nums, int idx) {
        result.push_back(track);
        for(int i=idx; i<nums.size(); i++) {
            if(i>idx && nums[i] == nums[i-1]) continue; // 同一树层去重
            track.push_back(nums[i]);
            backtrack(nums, i+1);
            track.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        track.clear();
        sort(nums.begin(), nums.end());
        backtrack(nums, 0);
        return result;
    }
};


// 先排序再用 used数组 去重
// used [i - 1] == true，说明同一   树枝   nums [i - 1] 使用过
// used [i - 1] == false，说明同一  树层   nums [i - 1] 使用过
// 时间复杂度: O (n * 2^n)
// 空间复杂度: O (n)
class Solution_M2_D1 {
    vector<vector<int>> result;
    vector<int> track;
    vector<bool> used;
    void backtrack(vector<int>& nums, int idx) {
        result.push_back(track);
        for(int i=idx; i<nums.size(); i++) {
            if(i > idx && nums[i] == nums[i-1] && used[i-1] == false) continue; // 同一树层去重
            used[i] = true;
            track.push_back(nums[i]);
            backtrack(nums, i + 1);
            used[i] = false;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        track.clear();
        if(nums.size() == 0) return result;
        used = vector<bool>(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtrack(nums, 0);
        return result; 
    }
};



// 先排序在使用set去重
class Solution_D3_copy {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);
        unordered_set<int> uset;
        for (int i = startIndex; i < nums.size(); i++) {
            if (uset.find(nums[i]) != uset.end()) {
                continue;
            }
            uset.insert(nums[i]);
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end()); // 去重需要排序
        backtracking(nums, 0);
        return result;
    }
};


// 先排序再数组替代hash去重
class Solution_D3_M {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);
        int set[21] = {0};
        for (int i = startIndex; i < nums.size(); i++) {
            if (set[nums[i] + 10] != 0) {
                continue;
            }
            set[nums[i] + 10] = 1;
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        sort(nums.begin(), nums.end()); // 去重需要排序
        backtracking(nums, 0);
        return result;
    }
};