// https://leetcode.cn/problems/merge-intervals
// 56. 合并区间
// labuladong 题解思路
// 中等
// 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
// 请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

// 示例 1：
// 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
// 输出：[[1,6],[8,10],[15,18]]
// 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

// 示例 2：
// 输入：intervals = [[1,4],[4,5]]
// 输出：[[1,5]]
// 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

// 提示：
// 1 <= intervals.length <= 10^4
// intervals[i].length == 2
// 0 <= starti <= endi <= 10^4


#include<iostream>
#include<vector>
#include<algorithm>
using std::sort;
using std::vector;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

    }
};


// 10:03--10:08(看题找思路)--10:16(忘记添加最后一个)--10:22
// 按左边界从小到大排序，然后融合
class Solution_M1 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        if(intervals.size() == 0) return result;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
            return a[0] < b[0]; // 左边界从小到大排序
        });
        int left = intervals[0][0];
        int right = intervals[0][1];
        for(int i=1; i<intervals.size(); i++) {
            if(intervals[i][0] <= right) {
                right = std::max(right, intervals[i][1]);
            }
            else {
                result.push_back(vector<int>{left, right});
                left = intervals[i][0];
                right = intervals[i][1];
            }
        }
        // 忘记了最后一个
        result.push_back(vector<int>{left, right}); // ***
        return result;
    }
};



// 时间复杂度: O (nlogn)
// 空间复杂度: O (logn)，排序需要的空间开销
class Solution_D1 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        if(intervals.size() == 0) return result;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){
            return a[0] < b[0]; // 左边界从小到大排序
        });
        result.push_back(intervals[0]); // 直接在result上改边界
        for(int i=1; i<intervals.size(); i++) {
            if(intervals[i][0] <= result.back()[1]) {
                result.back()[1] = std::max(result.back()[1], intervals[i][1]);
            }
            else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};







// 2024年5月7日
// 15:23--15:47
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        if(intervals.size() < 1) return result;
        // 升序排列
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if(a[0] == b[0]) return a[1] < b[1];
            else return a[0] < b[0];
        });
        int start = intervals[0][0];
        int end = intervals[0][1];
        for(int i=1; i<intervals.size(); i++) {
            // 跟上一个有重合，继续扩大区域
            if(intervals[i][0] <= end) {
                end = std::max(end, intervals[i][1]);
            }
            else {  // 无重合，重新开始
                result.push_back({start, end});
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }
        // 最后一个
        result.push_back({start, end}); // ***
        return result;
    }
};