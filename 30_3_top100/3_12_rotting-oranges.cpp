// https://leetcode.cn/problems/rotting-oranges/submissions/552816403/?envType=study-plan-v2&envId=top-100-liked
// 994. 腐烂的橘子
// 中等
// 相关标签
// 相关企业
// 在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：

// 值 0 代表空单元格；
// 值 1 代表新鲜橘子；
// 值 2 代表腐烂的橘子。
// 每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

// 返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。

 

// 示例 1：



// 输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
// 输出：4
// 示例 2：

// 输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
// 输出：-1
// 解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。
// 示例 3：

// 输入：grid = [[0,2]]
// 输出：0
// 解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
 

// 提示：

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 10
// grid[i][j] 仅为 0、1 或 2


#include<iostream>
#include<vector>
#include<queue>
using namespace std;



// 2024年8月5日
// 22:25--22:39--23:07
// 多源广度优先遍历
// 将最开始所有腐烂的橘子作为第一层
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> used = vector<vector<int>>(m, vector<int>(n, 0));
        queue<pair<int, int>> q;
        int fresh = 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 2) {
                    q.push({i, j}); // 将腐烂的橘子加入
                    used[i][j] = 1;
                }
                else if(grid[i][j] == 1) {
                    fresh++;    // 统计新鲜的橘子
                }
            }
        }
        int res = 0;
        while(!q.empty() && fresh) {    // *** 可以不要 fresh，而且写成了 !fresh
            int num = q.size(); // *** 写成了 n 和上面的重复了
            int rotten = false;
            for(int i=0; i<num; i++) {  // 忘了 for循环
                pair<int, int> cur = q.front();
                q.pop();
                for(int i=0; i<4; i++) {
                    int nx = cur.first + dir[i][0];
                    int ny = cur.second + dir[i][1];
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(used[nx][ny] || grid[nx][ny] == 0) continue;
                    q.push({nx, ny});
                    used[nx][ny] = 1;
                    fresh--;
                    rotten = true;
                }
            }
            if(rotten) res++;   // 只有传染才增加   ***
        }
        return fresh == 0 ? res : -1;
    }
};