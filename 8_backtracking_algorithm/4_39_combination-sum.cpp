// 39. 组合总和
// 中等
// 给你一个 无重复元素的整数数组 candidates 和一个目标整数 target ，
// 找出 candidates 中可以使数字和为目标数 target 的所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。
// candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 
// 对于给定的输入，保证和为 target 的不同组合数少于 150 个。

// 提示：
// 1 <= candidates.length <= 30
// 2 <= candidates[i] <= 40
// candidates 的所有元素 互不相同
// 1 <= target <= 40


// 本题还需要 startIndex 来控制 for 循环的起始位置，对于组合问题，什么时候需要 startIndex 呢？
// 如果是一个集合来求组合的话，就需要 startIndex，例如：77. 组合，216. 组合总和 III。
// 如果是多个集合取组合，各个集合之间相互不影响，那么就不用 startIndex，例如：17. 电话号码的字母组合


#include<iostream>
#include<vector>
using std::vector;

// ~16:10--16:15--16:18(有重复)--16:23(改错)
// candidates = [2,3,6,7]
// target = 7
// 输出：[[2,2,3],[2,3,2],[3,2,2],[7]]
// 预期结果：[[2,2,3],[7]]
// 时间复杂度: O (n * 2^n)，注意这只是复杂度的上界，因为剪枝的存在，真实的时间复杂度远小于此
// 空间复杂度: O (target)
class Solution_M1 {
    vector<vector<int>> result;
    vector<int> track;
    int sum = 0;
    void backtrack(const vector<int>& candidates, const int& target, int idx) {
        if(sum >= target) {
            if(sum == target) result.push_back(track);
            return;
        }
        for(int i=idx; i<candidates.size(); i++) {
            sum += candidates[i];
            track.push_back(candidates[i]);
            // 后面的递归都从 i 开始，防止重复
            // 不是 i+1 了 表示可以重复读取当前的数
            backtrack(candidates, target, i);   // ***
            sum -= candidates[i];
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        track.clear();
        sum = 0;
        backtrack(candidates, target, 0);
        return result;
    }
};


// 剪枝优化
// 也可以排序后剪枝，这样可以直接 break 或 return 了
class Solution_M2 {
    vector<vector<int>> result;
    vector<int> track;
    int sum = 0;
    void backtrack(const vector<int>& candidates, const int& target, int idx) {
        if(sum >= target) {
            if(sum == target) result.push_back(track);
            return;
        }
        for(int i=idx; i<candidates.size(); i++) {
            sum += candidates[i];
            if(sum > target) {
                sum -= candidates[i];   // 回溯
                continue;               // 不能使用 break 或 return 因为candidates不是有序数组
            }
            track.push_back(candidates[i]);
            backtrack(candidates, target, i);   //
            sum -= candidates[i];
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        track.clear();
        sum = 0;
        backtrack(candidates, target, 0);
        return result;
    }
};