// 435. 无重叠区间
// labuladong 题解思路
// 中等
// 给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。返回 需要移除区间的最小数量，使剩余区间互不重叠 。

// 示例 1:
// 输入: intervals = [[1,2],[2,3],[3,4],[1,3]]
// 输出: 1
// 解释: 移除 [1,3] 后，剩下的区间没有重叠。

// 示例 2:
// 输入: intervals = [ [1,2], [1,2], [1,2] ]
// 输出: 2
// 解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。

// 示例 3:
// 输入: intervals = [ [1,2], [2,3] ]
// 输出: 0
// 解释: 你不需要移除任何区间，因为它们已经是无重叠的了。

// 提示:
// 1 <= intervals.length <= 10^5
// intervals[i].length == 2
// -5 * 10^4 <= starti < endi <= 5 * 10^4


#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using std::unordered_set;
using std::sort;
using std::vector;
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {

    }
};


// 11:50--12:18(错误)--12:21(处理无重合时的情况)
// 排序后移除重叠的最大的区间
// 输入
// intervals =
// [[0,2],[1,3],[2,4],[3,5],[4,6]]
// 输出
// 1
// 预期结果
// 2
class Solution_M1 {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.size() < 2) return 0;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if(a[0] == b[0]) return a[1] > b[1];    // 起点相同时按终点从大到小排
            return a[0] < b[0];                     // 起点不同时按起点从小到大排
        });
        int start = intervals[0][0];
        int end = intervals[0][1];
        int result = 0;
        for(int i=1; i<intervals.size(); i++) {
            if(intervals[i][0] < end && intervals[i][1] > end) {    // 交叉时 end 不变，删除 i
                result++;
            }
            else if(intervals[i][1] <= end) {    // 包含时 end变小，删除 i-1
                result++;
                end = intervals[i][1];
            }
            else {
                end = intervals[i][1];          // 无重合时 end变大，不用删除   ***
            }
        }
        return result;
    }
};


//14:06--14:26
// 只排序起点
class Solution_M2 {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.size() < 2) return 0;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0]; // 起点从小到大排序
        });
        int result = 0;
        int end = intervals[0][1];
        for(int i=1; i<intervals.size(); i++) {
            if(intervals[i][0] < end) {   // 大包小或交叉
                result++;
                end = end < intervals[i][1] ? end : intervals[i][1];    // 删掉 end 大的那个
            }
            else {
                end = intervals[i][1];
            }
        }
        return result;
    }
};

// 14:30--14:39
// 只排序终点（按右边界从小到大排序）
class Solution_M3 {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.size() < 2) return 0;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1]<b[1];   // 右边界从小到大排序
        });
        int result = 0;
        int end = intervals[0][1];
        for(int i=1; i<intervals.size(); i++) {
            if(intervals[i][0] < end) { // 当前左边界小于上一个的右边界，一定是包含或交叉，由于排过序，当前右边界小于上一个右边界
                result++;               // 删除当前区间，因此右边界不用变
            }
            else {                      // 当前左边界大于等于左边界，添加当前区间，更新右边界
                end = intervals[i][1];
            }
        }
        return result;
    }
};


// 时间复杂度：O (nlog n) ，有一个快排
// 空间复杂度：O (n)，有一个快排，最差情况 (倒序) 时，需要 n 次递归调用。因此确实需要 O (n) 的栈空间
class Solution_D1_copy {
public:
    // 按照区间右边界排序
    static bool cmp (const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return 0;
        sort(intervals.begin(), intervals.end(), cmp);
        int count = 1; // 记录非交叉区间的个数
        int end = intervals[0][1]; // 记录区间分割点
        for (int i = 1; i < intervals.size(); i++) {
            if (end <= intervals[i][0]) {
                end = intervals[i][1];
                count++;
            }
        }
        return intervals.size() - count;
    }
};

