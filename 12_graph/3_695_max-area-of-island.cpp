// 695. 岛屿的最大面积
// labuladong 题解思路
// 中等
// 给你一个大小为 m x n 的二进制矩阵 grid 。
// 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。
// 你可以假设 grid 的四个边缘都被 0（代表水）包围着。
// 岛屿的面积是岛上值为 1 的单元格的数目。
// 计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。

// 示例 1：
// 输入：grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
// 输出：6
// 解释：答案不应该是 11 ，因为岛屿只能包含水平或垂直这四个方向上的 1 。

// 示例 2：
// 输入：grid = [[0,0,0,0,0,0,0,0]]
// 输出：0

// 提示：
// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 50
// grid[i][j] 为 0 或 1


#include<iostream>
#include<vector>
#include<queue>
using std::max;
using std::queue;
using std::pair;
using std::vector;

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {

    }
};

// 11:12--11:16(看题找思路)--11:40
// 广度优先遍历，只有陆地的格子才会被加入队列，记录岛屿的最大面积
class Solution_M1_D1 {
    vector<vector<bool>> used;
    int m, n;
    int result = 0;
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    int bfs(vector<vector<int>>& grid, int x, int y) {
        int res = 1;
        queue<pair<int, int>> que;
        que.push({x, y});
        used[x][y] = true;  // 加入即标注
        while(!que.empty()) {
            pair<int, int> cur = que.front();
            que.pop();
            for(int i=0; i<4; i++) {
                int next_x = cur.first + dir[i][0];
                int next_y = cur.second + dir[i][1];
                // 超出索引
                if(next_x < 0 || next_x >= m || next_y < 0 || next_y >= n) continue;
                // 海洋或已被标记过
                if(grid[next_x][next_y] == 0 || used[next_x][next_y]) continue;
                // 未被标注的陆地
                que.push({next_x, next_y});
                used[next_x][next_y] = true;    // 加入即标注
                res++;
            }
        }
        return res;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        used = vector<vector<bool>>(m, vector<bool>(n, false));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(!used[i][j] && grid[i][j] == 1) {
                    int curA = bfs(grid, i, j);
                    result = result > curA ? result : curA;
                }
            }
        }
        return result;
    }
};


// 11:42--11:58
// 深度优先遍历，不使用淹没的手段
class Solution_M2 {
    vector<vector<bool>> used;
    int m, n;
    int res = 0;
    int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
    int dfs(vector<vector<int>>& grid, int x, int y) {
        if(x < 0 || x >= m || y < 0 || y >= n) return 0;
        if(used[x][y] || grid[x][y] == 0) return 0;
        // 未被标注的陆地
        used[x][y] = true;
        int res = 1;
        for(int i=0; i<4; i++) {
            int next_x = x + dir[i][0];
            int next_y = y + dir[i][1];
            res += dfs(grid, next_x, next_y);
        }
        return res;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int result = 0;
        m = grid.size();
        n = grid[0].size();
        used = vector<vector<bool>>(m, vector<bool>(n, false));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(!used[i][j] && grid[i][j] == 1) {
                    int cur = dfs(grid, i, j);
                    result  = result > cur ? result : cur;
                }
            }
        }
        return result;
    }
};


// 深度优先遍历，使用淹没的手段
class Solution_M3_L1 {
    int m, n;
    int res = 0;
    int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
    int dfs(vector<vector<int>>& grid, int x, int y) {
        if(x < 0 || x >= m || y < 0 || y >= n) return 0;
        if(grid[x][y] == 0) return 0;
        // 未被淹没的陆地
        grid[x][y] = 0;
        int res = 1;
        for(int i=0; i<4; i++) {
            int next_x = x + dir[i][0];
            int next_y = y + dir[i][1];
            res += dfs(grid, next_x, next_y);
        }
        return res;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int result = 0;
        m = grid.size();
        n = grid[0].size();
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1) {
                    int cur = dfs(grid, i, j);
                    result  = result > cur ? result : cur;
                }
            }
        }
        return result;
    }
};



// 深度优先遍历，极致节省内存
class Solution_M3_L1_2 {
    int m, n;
    int dfs(vector<vector<int>>& grid, int x, int y) {
        if(x < 0 || x >= m || y < 0 || y >= n) return 0;
        if(grid[x][y] == 0) return 0;
        // 未被淹没的陆地
        grid[x][y] = 0;
        return 1 + dfs(grid, x+1, y)
                + dfs(grid, x-1, y)
                + dfs(grid, x, y+1)
                + dfs(grid, x, y-1);
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int result = 0;
        m = grid.size();
        n = grid[0].size();
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1) {
                    result = max(result, dfs(grid, i, j));
                }
            }
        }
        return result;
    }
};