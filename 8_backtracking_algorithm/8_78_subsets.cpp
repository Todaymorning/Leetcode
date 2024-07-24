// 78. 子集
// labuladong 题解思路
// 中等
// 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
// 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

// 示例 1：
// 输入：nums = [1,2,3]
// 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

// 示例 2：
// 输入：nums = [0]
// 输出：[[],[0]]
 
// 提示：
// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10
// nums 中的所有元素 互不相同

#include<iostream>
#include<vector>
using std::vector;


// 11:18--11:27
// 返回的顺序不太一样
// 输入nums =[1,2,3]
// 输出[[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]
// 预期结果[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
// 时间复杂度: O (n * 2^n)
// 空间复杂度: O (n)
class Solution_M1 {
    vector<vector<int>> result;
    vector<int> track;
    void backtrack(vector<int>& nums, int idx) {
        if(!track.empty()) result.push_back(track);
        for(int i=idx; i<nums.size(); i++) {
            track.push_back(nums[i]);
            backtrack(nums, i + 1);
            track.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        result.clear();
        result.push_back(vector<int>());
        if(nums.size() == 0) return result;
        backtrack(nums, 0);
        return result;
    }
};



class Solution_D1_copy {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path); // 收集子集，要放在终止添加的上面，否则会漏掉自己
        if (startIndex >= nums.size()) { // 终止条件可以不加
            return;
        }
        for (int i = startIndex; i < nums.size(); i++) {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
};

