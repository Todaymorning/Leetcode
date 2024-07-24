// 46. 全排列
// 中等
// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

// 示例 1：
// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

// 示例 2：
// 输入：nums = [0,1]
// 输出：[[0,1],[1,0]]

// 示例 3：
// 输入：nums = [1]
// 输出：[[1]]
 
// 提示：
// 1 <= nums.length <= 6
// -10 <= nums[i] <= 10
// nums 中的所有整数 互不相同


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {

    }
};

// 16:52--17:05--成功
// 使用 used 数组标记已经使用过的数字，使用j进行索引，每次循环 j++，找下一个受害者
class Solution_M1 {
    vector<vector<int>> result;
    vector<int> track;
    vector<bool> used;
    void backtrack(vector<int>& nums) {
        if(track.size() == nums.size()) result.push_back(track);
        for(int i=0, j=0; i<nums.size() - track.size(); i++, j++) {
            while(used[j] == true && j<used.size()) j++;    // 找到一个没用过的数
            if(j == used.size()) return;    // 所有数都被用了
            used[j] = true;
            track.push_back(nums[j]);
            backtrack(nums);
            used[j] = false;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.size() == 0) return result;
        result.clear();
        track.clear();
        used = vector<bool>(nums.size(), false);
        backtrack(nums);
        return result;
    }
};


// 查看D1的思路，回看写过的代码，发现for循环中的i没咋使用，可以只用一个i也实现上面的功能，且逻辑更清晰
// 时间复杂度: O (n!)
// 空间复杂度: O (n)
// 总结：
// 排列问题的不同：
// 每层都是从 0 开始搜索而不是 idx
// 需要 used 数组记录 path 里都放了哪些元素了
class Solution_D1_M1 {
    vector<vector<int>> result;
    vector<int> track;
    vector<bool> used;
    void backtrack(vector<int>& nums) {
        if(track.size() == nums.size()) result.push_back(track);
        for(int i=0; i<nums.size() - track.size(); i++) {
            if(used[i] == true) continue;    // 找到一个没用过的数
            used[i] = true;
            track.push_back(nums[i]);
            backtrack(nums);
            used[i] = false;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.size() == 0) return result;
        result.clear();
        track.clear();
        used = vector<bool>(nums.size(), false);
        backtrack(nums);
        return result;
    }
};


// 2024年4月30日
// 11:09
// 回溯，不含重复数字
class Solution {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;
    void backtrack(const vector<int>& nums) {
        if(path.size() == nums.size()) result.push_back(path);
        for(int i=0; i<nums.size(); i++) {
            if(used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtrack(nums);
            path.pop_back();
            used[i] = false;
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        used.resize(nums.size(), false);
        backtrack(nums);
        return result;
    }
};