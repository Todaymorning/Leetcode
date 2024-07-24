// 47. 全排列 II
// 中等
// 给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。

// 示例 1：
// 输入：nums = [1,1,2]
// 输出：
// [[1,1,2],
//  [1,2,1],
//  [2,1,1]]

// 示例 2：
// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
 
// 提示：
// 1 <= nums.length <= 8
// -10 <= nums[i] <= 10

#include<iostream>
#include<vector>
#include<algorithm>
using std::sort;
using std::vector;
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        return vector<vector<int>>();
    }
};

// 需要同一树层去重，由于不强调顺序，可以考虑排序和不排序两种解题思路



// 18:15--18:23(有个小错误 索引+10)
// 用数组替代hash，树层去重，这样就不用排序了
class Solution_M1 {
    vector<vector<int>> result;
    vector<int> track;
    vector<bool> used;
    void backtrack(vector<int>& nums) {
        if(track.size() == nums.size()) result.push_back(track);
        // 同一树层去重
        int set[21] = {0};
        for(int i=0; i<int(nums.size()); i++) {
            if(used[i] == true) continue;   // 找到没有过的数字
            if(set[nums[i] + 10] == 1) continue; // 同一树层已经用过该数字
            set[nums[i] + 10] = 1;
            used[i] = true;
            track.push_back(nums[i]);
            backtrack(nums);
            used[i] = false;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        result.clear();
        track.clear();
        if(nums.size() == 0) return result;
        used = vector<bool>(nums.size(), false);
        backtrack(nums);
        return result;
    }
};



// 由于是按任意顺序返回都可以，这里也可以先排序再做全排列
// 这样的话可以用到如下去重的方法：
// 对树层去重
// if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
//     continue;
// }
// 对树枝去重
// if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == true) {
//     continue;
// }

// 14:31--14:40(错误)--14:56(漏了两句)
// 时间复杂度: 最差情况所有元素都是唯一的。复杂度和全排列1都是 O(n! * n) 对于 n 个元素一共有 n! 种排列方案。
// 而对于每一个答案，我们需要 O(n) 去复制最终放到 result 数组
// 空间复杂度: O(n) 回溯树的深度取决于我们有多少个元素
class Solution_D1_M2 {
    vector<vector<int>> result;
    vector<int> track;
    vector<bool> used;
    void backtrack(vector<int>& nums) {
        if(track.size() == nums.size()) result.push_back(track);
        for(int i=0; i<int(nums.size()); i++) {
            // 同一树枝上跳过使用过的那个
            if(used[i] == true) continue;
            // 如果同一树层nums[i - 1]使用过则直接跳过
            if(i>0 && nums[i] == nums[i-1] && used[i-1] == false) continue;
            used[i] = true;
            track.push_back(nums[i]);
            backtrack(nums);
            used[i] = false;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        result.clear();
        track.clear();
        used = vector<bool>(nums.size(), false);    // ***
        if(nums.size() == 0) return result;
        sort(nums.begin(), nums.end()); // 默认升序排列
        backtrack(nums);
        return result;
    }
};


// int main() {
//     vector<int> nums = {1, 1, 2};
//     Solution_D1_M2 s;
//     auto reuslt = s.permuteUnique(nums);
//     return 0;
// }



// https://www.programmercarl.com/%E5%9B%9E%E6%BA%AF%E7%AE%97%E6%B3%95%E5%8E%BB%E9%87%8D%E9%97%AE%E9%A2%98%E7%9A%84%E5%8F%A6%E4%B8%80%E7%A7%8D%E5%86%99%E6%B3%95.html#_47-%E5%85%A8%E6%8E%92%E5%88%97-ii
// 数组替代hash，同一树层去重
class Solution_18_add {
    vector<vector<int>> result;
    vector<int> track;
    vector<bool> used;
    void backtrack(vector<int>& nums) {
        if(track.size() == nums.size()) result.push_back(track);
        int set[21] = {0};
        for(int i=0; i<nums.size(); i++) {
            if(used[i] == true) continue;
            if(set[nums[i] + 10] == 1) continue;
            set[nums[i] + 10] = 1;
            used[i] = true;
            track.push_back(nums[i]);
            backtrack(nums);
            used[i] = false;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        result.clear();
        track.clear();
        if(nums.size() == 0) return result;
        used = vector<bool>(nums.size(), false);
        backtrack(nums);
        return result;
    }
};















// 21:35--21:53
// 排列中的数字可以重复，但全排列本身不能重复
class Solution {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> u;
    void backtracking(vector<int>& nums, int n) {
        if(n == nums.size()) {
            result.push_back(path);
        }
        int used[21] = {0};
        for(int i=0; i<nums.size(); i++) {
            // 同一树层去重
            if(used[nums[i] + 10]) continue;
            // 不使用重复数字
            if(u[i]) continue;
            used[nums[i] + 10] = 1;
            u[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, n+1);
            u[i] = false;
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        u.resize(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return result;
    }
};