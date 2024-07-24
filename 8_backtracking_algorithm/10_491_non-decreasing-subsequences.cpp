// 491. 递增子序列
// 中等
// 给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，递增子序列中 至少有两个元素 。你可以按 任意顺序 返回答案。
// 数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。

// 示例 1：
// 输入：nums = [4,6,7,7]
// 输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

// 示例 2：
// 输入：nums = [4,4,3,2,1]
// 输出：[[4,4]]
 
// 提示：
// 1 <= nums.length <= 15
// -100 <= nums[i] <= 100



#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using std::unordered_set;
using std::vector;
using std::sort;


// 15:40--15:47(错误,没有去重)--15:52(错误)--16:01(开始看思路)
// nums =[4,6,7,7]
// 输出[[4,6],[4,6,7],[4,6,7,7],[4,6,7],[4,7],[4,7,7],[4,7],[6,7],[6,7,7],[6,7],[7,7]]
// 预期结果[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
// 错误，有关 1 的重复了
// nums = [1,2,3,4,5,6,7,8,9,10,1,1,1,1,1]

#if 0
class Solution_M1 {
    vector<vector<int>> result;
    vector<int> track;
    void backtrack(vector<int>& nums, int idx) {
        if(track.size() > 1) result.push_back(track);
        for(int i=idx; i<int(nums.size()); i++) {
            if(i>idx && nums[i] == nums[i-1]) continue; // 同一树层去重
            if(!track.empty() && nums[i]<track.back()) continue;    // 当前数字比track中最后一位小，继续
            track.push_back(nums[i]);
            backtrack(nums, i + 1);
            track.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        result.clear();
        track.clear();
        if(nums.size() < 2) return result;
        backtrack(nums, 0);
        return result;
    }
};

// int main() {
//     Solution s;
//     vector<int> nums = {1,2,3,4,5,6,7,8,9,10,1,1,1,1,1};
//     auto result = s.findSubsequences(nums);
//     for(int i=0; i<result.size(); i++) {
//         for(int j = 0; j<result[i].size(); j++) {
//             std::cout << result[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
//     return 0;
// }
#endif


// 16:23--16:34
// 看过思路后知道使用 unordered_set 对本层元素进行去重
// 因为这里不能排序
// 时间复杂度: O (n * 2^n)
// 空间复杂度: O (n)
class Solution_D1_M2 {
    vector<vector<int>> result;
    vector<int> track;
    void backtrack(vector<int>& nums, int idx) {
        if(track.size() >= 2) result.push_back(track);
        // 本层的 unordered_map，检测同一树层中是否使用同一元素
        // 如nums=[4, 7, 6, 7] 现在是第二层，第一层已经选了 4，现在可以有如下选择
        // [4,7...], [4,6...], [4,7...]
        // 这时第一种和第三种情况就重复了，需要去掉
        unordered_set<int> uset;
        for(int i=idx; i<nums.size(); i++) {
            if(!track.empty() && track.back() > nums[i]) continue;  // 后一元素不能比迁移元素小
            if(uset.find(nums[i]) != uset.end()) continue;          // 用过的不能再用了 ***
            uset.insert(nums[i]);   // ***
            track.push_back(nums[i]);
            backtrack(nums, i+1);
            track.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        result.clear();
        track.clear();
        if(nums.size() < 2) return result;
        backtrack(nums, 0);
        return result;
    }
};



// 数值的范围是 [-100, 100]
// 优化，用数组做 hash，提高效率
class Solution_D2_copy {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int startIndex) {
        if (path.size() > 1) {
            result.push_back(path);
        }
        int used[201] = {0}; // 这里使用数组来进行去重操作，题目说数值范围[-100, 100]
        for (int i = startIndex; i < nums.size(); i++) {
            if ((!path.empty() && nums[i] < path.back())
                    || used[nums[i] + 100] == 1) {
                    continue;
            }
            used[nums[i] + 100] = 1; // 记录这个元素在本层用过了，本层后面不能再用了
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        result.clear();
        path.clear();
        backtracking(nums, 0);
        return result;
    }
};

