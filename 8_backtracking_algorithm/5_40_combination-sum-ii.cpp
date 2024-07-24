// 40. 组合总和 II
// labuladong 题解
// 中等
// 给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
// candidates 中的每个数字在每个组合中只能使用一次。

// 提示:
// 1 <= candidates.length <= 100
// 1 <= candidates[i] <= 50
// 1 <= target <= 30

// 注意：
// candidates可能会有重复的数字，且乱序


// 同一树枝上的都是同一个集合里的元素，不用去重
// 同一树层上的是不同集合，需要去重

#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using std::unordered_set;
using std::sort;
using std::vector;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {

    }
};


// 排序后使用idx去重
// 16:50--17:00(写)--17:02(错误)--17:07(改为排序方案)--17:08(没有考虑重复元素)--17:12(不会改)
// 数组中有重复的数字，因此需要排序后重新选取
// candidates = [10,1,2,7,6,1,5]
// target = 8
// 输出[[1,2,5],[1,7],[1,6,1],[2,6],[2,1,5],[7,1]]
// 预期结果[[1,1,6],[1,2,5],[1,7],[2,6]]
#if 0
class Solution {
    vector<vector<int>> result;
    vector<int> track;
    int sum = 0;
    void backtrack(const vector<int>& candidates, int target, int idx) {
        if(sum >= target) {
            if(sum == target) result.push_back(track);
            return;
        }
        for(int i=idx; i<candidates.size(); i++) {
            sum += candidates[i];
            if(sum > target) {  // 剪枝
                sum -= candidates[i];
                continue;       // candidates不是有序数组，因此需要继续
            }
            track.push_back(candidates[i]);
            backtrack(candidates, target, i + 1);
            sum -= candidates[i];
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        result.clear();
        track.clear();
        sum = 0;
        backtrack(candidates, target, 0);
        return result;
    }
};
#endif

// candidates = [10,1,2,7,6,1,5]
// target = 8
// 输出[[1,1,6],[1,2,5],[1,7],[1,2,5],[1,7],[2,6]]
// 预期结果[[1,1,6],[1,2,5],[1,7],[2,6]]
// 写完 Solution_M1_D1 后参考 D2 加上一个语句
#if 1
class Solution {
    vector<vector<int>> result;
    vector<int> track;
    int sum = 0;
    void backtrack(const vector<int>& candidates, int target, int idx) {
        if(sum >= target) {
            if(sum == target) result.push_back(track);
            return;
        }
        for(int i=idx; i<candidates.size(); i++) {
            if(i > idx && candidates[i] == candidates[i-1]) continue;   // 使用 idx 去重    ***
            sum += candidates[i];
            if(sum > target) {  // 剪枝
                sum -= candidates[i];
                return; // candidates已经是升序数组，可以直接return 或 break
            }
            track.push_back(candidates[i]);
            backtrack(candidates, target, i + 1);
            sum -= candidates[i];
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        result.clear();
        track.clear();
        sum = 0;
        sort(candidates.begin(), candidates.end()); // 默认进行升序排列
        backtrack(candidates, target, 0);
        return result;
    }
};
#endif


// 排序后used数组去重
// 20:47--21:01--21:08(改错)
// 看了D1的思路后写出
// used [i - 1] == true，说明同一   树枝   candidates [i - 1] 使用过
// used [i - 1] == false，说明同一  树层   candidates [i - 1] 使用过
// 时间复杂度: O (n * 2^n)
// 空间复杂度: O (n)
class Solution_M1_D1 {
    vector<vector<int>> result;
    vector<int> track;
    vector<int> used;
    int sum = 0;
    void backtrack(const vector<int>& candidates, int target, int idx) {
        if(sum >= target) {
            if(sum == target) result.push_back(track);
            return;
        }
        for(int i=idx; i<candidates.size(); i++) {
            // 去重，同一树层不能重复，同一树枝可以重复
            if(i > 0 && candidates[i-1] == candidates[i] && used[i-1] == 0) continue;   // i > 0 ***
            sum += candidates[i];
            if(sum > target) {  // 剪枝
                sum -= candidates[i];
                return; // candidates已经是升序数组，可以直接return 或 break
            }
            used[i] = 1;
            track.push_back(candidates[i]);

            backtrack(candidates, target, i+1);   // i+1 不使用同一个数字 *** 

            sum -= candidates[i];
            used[i] = 0;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        result.clear();
        track.clear();
        sum = 0;
        // 首先把给candidates排序，让其相同的元素都挨在一起。
        sort(candidates.begin(), candidates.end());   // 也可以自定义比较函数
        used = vector<int>(candidates.size(), 0);       // 全部置零
        backtrack(candidates, target, 0);
        return result;
    }
};


// 排序后使用hash数组去重
// 16:25--16:34--16:38
class Solution {
    vector<vector<int>> result;
    vector<int> track;
    int sum = 0;
    void backtrack(vector<int>& candidates, int target, int idx) {
        if(sum >= target){
            if(sum == target) result.push_back(track);
            return;
        }
        int set[50] = {0};
        for(int i=idx; i<candidates.size(); i++) {
            if(set[candidates[i]] == 1) continue;   // 同一树层去重
            if(sum > target) return;    // 剪枝
            set[candidates[i]] = 1;     // 忘了 ***
            sum += candidates[i];
            track.push_back(candidates[i]);
            backtrack(candidates, target, i + 1);
            sum -= candidates[i];
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        result.clear();
        track.clear();
        sum = 0;
        if(candidates.size() == 0) return result;
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0);
        return result;
    }
};



// 排序后使用unordered_set去重
class Solution_copy {
private:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int sum, int startIndex) {
        if (sum == target) {
            result.push_back(path);
            return;
        }
        unordered_set<int> uset; // 控制某一节点下的同一层元素不能重复
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            if (uset.find(candidates[i]) != uset.end()) {
                continue;
            }
            uset.insert(candidates[i]); // 记录元素
            sum += candidates[i];
            path.push_back(candidates[i]);
            backtracking(candidates, target, sum, i + 1);
            sum -= candidates[i];
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        path.clear();
        result.clear();
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0);
        return result;
    }
};