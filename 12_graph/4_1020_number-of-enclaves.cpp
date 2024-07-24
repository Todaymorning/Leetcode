// 1020. 飞地的数量
// https://leetcode.cn/problems/number-of-enclaves/description/
// labuladong 题解思路
// 中等
// 给你一个大小为 m x n 的二进制矩阵 grid ，其中 0 表示一个海洋单元格、1 表示一个陆地单元格。
// 一次 移动 是指从一个陆地单元格走到另一个相邻（上、下、左、右）的陆地单元格或跨过 grid 的边界。
// 返回网格中 无法 在任意次数的移动中离开网格边界的陆地单元格的数量。

// 示例 1：
// 输入：grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
// 输出：3
// 解释：有三个 1 被 0 包围。一个 1 没有被包围，因为它在边界上。

// 示例 2：
// 输入：grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
// 输出：0
// 解释：所有 1 都在边界上或可以到达边界。

// 提示：
// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 500
// grid[i][j] 的值为 0 或 1


#include<iostream>
#include<vector>
#include<queue>
using std::queue;
using std::pair;
using std::vector;


class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {

    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 深度优先搜索

// 19:37--19:42(读题找思路)--19:56
// 深度优先遍历，先遍历四周的，将更四周联通的做上标记
// 遍历内部的，统计陆地单元格的个数
class Solution_M1 {
    vector<vector<bool>> used;
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    int m, n;
    // 计算单个岛屿大小并做上标记
    int dfs(vector<vector<int>>& grid, int x, int y) {
        // 超出索引
        if(x<0 || y<0 || x>=m || y>=n) return 0;
        // 海洋或已被标记过
        if(grid[x][y] == 0 || used[x][y]) return 0;
        // 未被标注的陆地
        used[x][y] = true;
        int res = 1;
        for(int i=0; i<4; i++) {
            res += dfs(grid, x+dir[i][0], y+dir[i][1]);
        }
        return res;
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int result = 0;
        m = grid.size();
        n = grid[0].size();
        used = vector<vector<bool>>(m, vector<bool>(n, false));
        // 标记四周
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(i==0 || i==m-1 || j==0 || j==n-1) {
                    if(grid[i][j] == 1 && !used[i][j]) {
                        dfs(grid, i, j);
                    }
                }
            }
        }
        // 计算内部飞地个数
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1 && !used[i][j]) {
                    result += dfs(grid, i, j);
                }
            }
        }
        return result;
    }
};


// [[0,0,1,1,1,0,1,1,1,0,1],
// [1,1,1,1,0,1,0,1,1,0,0],
// [0,1,0,1,1,0,0,0,0,1,0],
// [1,0,1,1,1,1,1,0,0,0,1],
// [0,0,1,0,1,1,0,0,1,0,0],
// [1,0,0,1,1,1,0,0,0,1,1],
// [0,1,0,1,1,0,0,0,1,0,0],
// [0,1,1,0,1,0,1,1,1,0,0],
// [1,1,0,1,1,1,0,0,0,0,0],
// [1,0,1,1,0,0,0,1,0,0,1]]
// 遍历四周的代码分开写，想提速————没用
class Solution_M1_D1 {
    vector<vector<bool>> used;
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    int m, n;
    // 计算单个岛屿大小并做上标记
    int dfs(vector<vector<int>>& grid, int x, int y) {
        // 超出索引
        if(x<0 || y<0 || x>=m || y>=n) return 0;
        // 海洋或已被标记过
        if(grid[x][y] == 0 || used[x][y]) return 0;
        // 未被标注的陆地
        used[x][y] = true;
        int res = 1;
        for(int i=0; i<4; i++) {
            res += dfs(grid, x+dir[i][0], y+dir[i][1]);
        }
        return res;
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int result = 0;
        m = grid.size();
        n = grid[0].size();
        used = vector<vector<bool>>(m, vector<bool>(n, false));
        // 标记首末行
        for(int i=0; i<m; i++) {
            if(grid[i][0] == 1 && !used[i][0]) dfs(grid, i, 0);
            if(grid[i][n-1] == 1 && !used[i][n-1]) dfs(grid, i, n-1);   // used[i][n-1] 写成了 [i][0]导致错误
        }
        // 标记首末列
        for(int j=0; j<n; j++) {
            if(grid[0][j] == 1 && !used[0][j]) dfs(grid, 0, j);
            if(grid[m-1][j] == 1 && !used[m-1][j]) dfs(grid, m-1, j);
        }
        // 计算内部飞地个数，只遍历中间即可
        for(int i=1; i<m-1; i++) {
            for(int j=1; j<n-1; j++) {
                if(grid[i][j] == 1 && !used[i][j]) {
                    result += dfs(grid, i, j);
                }
            }
        }
        return result;
    }
};

// 直接淹没岛屿————提速非常可观
class Solution_M1_D1 {
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    int m, n;
    // 计算单个岛屿大小并做上标记
    int dfs(vector<vector<int>>& grid, int x, int y) {
        // 超出索引
        if(x<0 || y<0 || x>=m || y>=n) return 0;
        // 海洋或已被标记过
        if(grid[x][y] == 0) return 0;
        // 未被标注的陆地
        grid[x][y] = 0;     // 淹没
        int res = 1;
        for(int i=0; i<4; i++) {
            res += dfs(grid, x+dir[i][0], y+dir[i][1]);
        }
        return res;
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int result = 0;
        m = grid.size();
        n = grid[0].size();
        // 标记首末行
        for(int i=0; i<m; i++) {
            if(grid[i][0] == 1) dfs(grid, i, 0);
            if(grid[i][n-1] == 1) dfs(grid, i, n-1);   // used[i][n-1] 写成了 [i][0]导致错误
        }
        // 标记首末列
        for(int j=0; j<n; j++) {
            if(grid[0][j] == 1) dfs(grid, 0, j);
            if(grid[m-1][j] == 1) dfs(grid, m-1, j);
        }
        // 计算内部飞地个数，只遍历中间即可
        for(int i=1; i<m-1; i++) {
            for(int j=1; j<n-1; j++) {
                if(grid[i][j] == 1) {
                    result += dfs(grid, i, j);
                }
            }
        }
        return result;
    }
};



// 直接淹没岛屿，不使用额外数组做标记
class Solution_D1_copy {
private:
    int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1}; // 保存四个方向
    int count; // 统计符合题目要求的陆地空格数量
    void dfs(vector<vector<int>>& grid, int x, int y) {
        grid[x][y] = 0; // 淹没
        count++;
        for (int i = 0; i < 4; i++) { // 向四个方向遍历
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            // 超过边界
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;
            // 不符合条件，不继续遍历
            if (grid[nextx][nexty] == 0) continue;

            dfs (grid, nextx, nexty);
        }
        return;
    }

public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // 从左侧边，和右侧边 向中间遍历
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 1) dfs(grid, i, 0);
            if (grid[i][m - 1] == 1) dfs(grid, i, m - 1);
        }
        // 从上边和下边 向中间遍历
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 1) dfs(grid, 0, j);
            if (grid[n - 1][j] == 1) dfs(grid, n - 1, j);
        }
        count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) dfs(grid, i, j);
            }
        }
        return count;
    }
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 广度优先搜索

// 20:34--20:53
// 淹没岛屿
// 忘记 if(next_x<0 || next_y<0 || next_x>=m || next_y>=n) continue;
class Solution_M2 {
    int m, n;
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    // 广度优先搜索，计算每个岛屿的大小，并用海水淹没岛屿
    int bfs(vector<vector<int>>& grid, int x, int y) {
        if(x < 0 || y < 0 || x >= m || y >= n) return 0;
        if(grid[x][y] == 0) return 0;       
        queue<pair<int,int>> que;
        que.push({x,y});
        grid[x][y] = 0;     // 加入队列的时候就标记，防止重复加入
        int res = 1;
        while(!que.empty()) {
            pair<int, int> cur = que.front();
            que.pop();
            for(int i=0; i<4; i++) {
                int next_x = cur.first + dir[i][0];
                int next_y = cur.second + dir[i][1];
                if(next_x<0 || next_y<0 || next_x>=m || next_y>=n) continue;    // ***
                if(grid[next_x][next_y] == 1) {
                    res++;
                    que.push({next_x, next_y}); // 加入队列，等下一轮搜索
                    grid[next_x][next_y] = 0;   // 加入队列的时候就标记，防止重复加入
                }
            }
        }
        return res;
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int result = 0;
        m = grid.size();
        n = grid[0].size();
        for(int i=0; i<m; i++) {
            if(grid[i][0] == 1) bfs(grid, i, 0);
            if(grid[i][n-1] == 1) bfs(grid, i, n-1);
        }
        for(int j=0; j<n; j++) {
            if(grid[0][j] == 1) bfs(grid, 0, j);
            if(grid[m-1][j] == 1) bfs(grid, m-1, j);
        }
        for(int i=1; i<m-1; i++) {
            for(int j=1; j<n-1; j++) {
                if(grid[i][j] == 1) {
                    result += bfs(grid, i, j);
                }
            }
        }
        return result;
    }
};
