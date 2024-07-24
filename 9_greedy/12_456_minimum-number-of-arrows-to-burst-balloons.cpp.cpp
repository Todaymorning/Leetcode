// 452. 用最少数量的箭引爆气球
// labuladong 题解思路
// 中等
// 有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，
// 其中 points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend 之间的气球。你不知道气球的确切 y 坐标。
// 一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 
// 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。
// 给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。

// 示例 1：
// 输入：points = [[10,16],[2,8],[1,6],[7,12]]
// 输出：2
// 解释：气球可以用2支箭来爆破:
// -在x = 6处射出箭，击破气球[2,8]和[1,6]。
// -在x = 11处发射箭，击破气球[10,16]和[7,12]。
// 示例 2：

// 输入：points = [[1,2],[3,4],[5,6],[7,8]]
// 输出：4
// 解释：每个气球需要射出一支箭，总共需要4支箭。
// 示例 3：

// 输入：points = [[1,2],[2,3],[3,4],[4,5]]
// 输出：2
// 解释：气球可以用2支箭来爆破:
// - 在x = 2处发射箭，击破气球[1,2]和[2,3]。
// - 在x = 4处射出箭，击破气球[3,4]和[4,5]。

// 提示:
// 1 <= points.length <= 10^5
// points[i].length == 2
// -2^31 <= xstart < xend <= 2^31 - 1


#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using std::unordered_set;
using std::sort;
using std::vector;
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {

    }
};

// 19:32--19:40(看题)--19:43(没思路)--19:48(看D1思路)--20:33(改错)--21:11(内存不够)
// 局部最优：当气球出现重叠，一起射，所用弓箭最少。全局最优：把所有气球射爆所用弓箭最少。
// 排序后从左往右射，一个气球的覆盖范围内气球重叠最多的时候射箭
// 内存溢出
// 19:48--20:23
// [[1,2147483647]]
#if 0
class Solution {
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0]; // 起点从小往大排序，感觉终点从小往大排也可以
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), cmp);
        vector<bool> burst(points.size(), false);
        int sum = 0;
        for(int i=0; i<points.size(); i++) {
            if(burst[i] == true) continue;  // 该气球已经爆了
            // 统计区间
            int start = points[i][0];
            int end = points[i][1];
            // 记录区间内每个点气球重合的个数
            vector<int> num(end - start + 1, 1);
            int j=i+1;  // ***
            while(j<points.size() && points[j][0] <= end) {    // 第 j 个起点在end前的气球  ***
                for(int k=points[j][0]; k<=points[j][1] && k<=end; k++) num[k-start]++; // ***
                j++;
            }
            // 找到最大的重合点及索引
            int max = -1;
            int idx = -1;
            for(int k=0; k<num.size(); k++) {
                if(num[k] > max) {
                    max = num[k];
                    idx = k;
                }
            }
            // 射箭
            sum++;
            // 删除射箭轨迹上的气球
            idx += start;
            j = i;
            while(j<points.size() && points[j][0] <= end) { // ***
                if(points[j][0] <= idx && points[j][1] >= idx) burst[j] = true; // ***
                j++;
            }
        }
        return sum;
    }
};
#endif

// 21:45--22:14(超出时间限制)--11:07(错误)
// 修改
#if 0
class Solution {
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0]; // 按照起点降序
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), cmp);
        vector<bool> brust(points.size(), false);
        int result = 0;
        for(int i=0; i<points.size(); i++) {
            if(brust[i] == true) continue;
            // int start = points[i][0];
            int end = points[i][1];
            // 在第 i 个气球范围内，找到气球重合最多的位置
            int max = -1;
            int idx = -1;
            // ***
            for(int next=i; next<points.size(); next++) {   // 只在每个气球的start处射箭
                // start 处
                int p = points[next][0];
                if(p > end) break;  // 到结尾了
                int num = 1;
                int k = i+1;
                while(k<points.size() && points[k][0] <= end) {    // 统计 points[next][0] 处有多少个重合的气球
                    if(points[k][0] <= p && points[k][1] >= p) num++;
                    k++;
                }
                if(num > max) {
                    max = num;
                    idx = p;    // idx处气球重合个数最多
                }
                // end 处
                p = points[next][1];
                if(p > end) continue;  // 到结尾了
                num = 1;
                k = i+1;
                while(k<points.size() && points[k][0] <= end) {    // 统计 points[next][0] 处有多少个重合的气球
                    if(points[k][0] <= p && points[k][1] >= p) num++;
                    k++;
                }
                if(num > max) {
                    max = num;
                    idx = p;    // idx处气球重合个数最多
                }
            }
            // 在 idx 处射箭：在第 i 个气球范围内，最多气球重合处射箭
            result++;
            // 标记射爆的气球
            for(int j=i; j<points.size() && points[j][0]<=end; j++) {
                if(points[j][0] <= idx && points[j][1] >= idx) {
                    brust[j] = true;
                }
            }
        }
        return result;
    }
};
#endif


// 局部最优：当气球出现重叠，一起射，所用弓箭最少。全局最优：把所有气球射爆所用弓箭最少。
// 将所有气球按起点从小往大排序
// 给一支箭，当前气球和前一个气球没重合的地方，需要另射一只箭
// 有重合的气球，更新终点为最小值
// 时间复杂度：O (nlog n)，因为有一个快排
// 空间复杂度：O (1)，有一个快排，最差情况 (倒序) 时，需要 n 次递归调用。因此确实需要 O (n) 的栈空间
class Solution_D1_M3 {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];     // 按起点从小到大排
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);
        int result = 1;
        int end = points[0][1]; // 每支箭可以移动的终点
        for(int i=1; i<points.size(); i++) {
            if(points[i][0] > end) { // 当前气球和前一个气球没重合的地方，需要另射一只箭
                result++;
                end = points[i][1]; // 下一支箭的终点
            }
            else {
                end = end < points[i][1] ? end : points[i][1];  // 有重合的气球，更新终点为最小值
            }
        }
        return result;
    }
};



// 13:55--14:04
class Solution_M4 {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.size() == 0) return 0;
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b){
            if(a[0] == b[0]) return a[1] > b[1];    // start相同时按end从大到小排序
            return a[0] < b[0];                     // start不同时按start从小到达排序
        });
        int result = 1;
        int end = points[0][1];
        for(int i=1; i<points.size(); i++) {
            if(points[i][1] < end) end = points[i][1];  // 大气球包含小气球时，end 范围缩小
            if(points[i][0] > end) {    // 气球不重合时，再加一支箭，更新end
                result++;
                end = points[i][1];
            }
        }
        return result;
    }
};