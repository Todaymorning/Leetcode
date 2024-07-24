// 77. 组合
// labuladong 题解思路
// 中等
// 给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
// 你可以按 任何顺序 返回答案。

// 提示：
// 1 <= n <= 20
// 1 <= k <= n

#include<iostream>
#include<vector>
using std::vector;


class Solution {
public:
    vector<vector<int>> combine(int n, int k) {

    }
};


// 10:06--10:12(尝试回溯 不会)
// 时间复杂度: O (n * 2^n)
// 空间复杂度: O (n)

class Solution_D1 {
    vector<vector<int>> result; // 存放符合条件结果的集合
    vector<int> path;           // 存放符合条件单一结果
    void backtrack(int n, int k, int startIndex) {
        // 终止条件
        if(path.size() == k) {
            result.push_back(path);
            return;
        }
        // 单层搜索过程：for 循环每次从 startIndex 开始遍历，然后用 path 保存取到的节点 i。
        // int max = n-(k-path.size())+1
        // for(int i=startIndex; i<=max; i++) // 剪枝优化
        for (int i = startIndex; i <= n; i++) { // 控制树的横向遍历
            path.push_back(i);          // 处理节点
            backtrack(n, k, i + 1);     // 递归：控制树的纵向遍历，注意下一层搜索要从i+1开始
            path.pop_back();            // 回溯，撤销处理的节点
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        result.clear(); // 可以不写
        path.clear();   // 可以不写
        backtrack(n, k, 1);
        return result;
    }
};


// 回溯解法
// 20:00--20:05(写成了排列，用到used进行同一树枝去重，这是错误的)--20:16
class Solution_re {
    vector<vector<int>> result;
    vector<int> track;
    void backtracking(int n, int k, int start) {    // 需要start
        if(track.size() == k) {
            result.push_back(track);
            return;
        }
        // 剪枝优化，从max之后开始时track就凑不满了，后面没必要遍历了
        // int max = n - (k-track.size()) + 1
        // for(int i=start; i<=max; i++)
        for(int i=start; i<=n; i++) {
            track.push_back(i);
            backtracking(n, k, i+1);    // i+1
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        result.clear();
        track.clear();
        backtracking(n, k, 1);
        return result;
    }
};