// 216. 组合总和 III
// 中等
// 找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：
// 只使用数字 1 到 9
// 每个数字 最多使用一次 
// 返回 所有可能的有效组合的列表 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。


// 提示:
// 2 <= k <= 9
// 1 <= n <= 60

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {

    }
};


// 11:07--11:15
class Solution_M1 {
    vector<vector<int>> result;
    vector<int> track;
    int sum = 0;
    void backtrack(int k, int n, int startNum) {
        if(sum > n || track.size() == k) {
            if(sum == n) result.push_back(track);
            return;
        }
        for(int i= startNum; i<=9; i++) {
            sum += i;
            track.push_back(i);
            backtrack(k, n, i+1);
            sum -= i;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        result.clear();
        track.clear();
        backtrack(k, n, 1);
        return result;
    }
};


// 剪枝
class Solution_M2 {
    vector<vector<int>> result;
    vector<int> track;
    int sum = 0;
    void backtrack(int k, int n, int startNum) {
        if(track.size() == k) {
            if(sum == n) result.push_back(track);
            return;
        }
        int max = 9 - (k - track.size()) + 1;
        for(int i= startNum; i<=max; i++) { // 剪枝 ***
            sum += i;
            // 剪枝
            if(sum > n) {
                sum -= i;   // break 前需要回溯 ***
                break;
            }
            track.push_back(i);
            backtrack(k, n, i+1);
            sum -= i;
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        result.clear();
        track.clear();
        backtrack(k, n, 1);
        return result;
    }
};
