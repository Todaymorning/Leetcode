// https://leetcode.cn/problems/number-of-islands
// 200. 岛屿数量
// labuladong 题解思路
// 中等
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和 / 或竖直方向上相邻的陆地连接形成。
// 此外，你可以假设该网格的四条边均被水包围。

// 示例 1：
// 输入：grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]
// 输出：1

// 示例 2：
// 输入：grid = [
//   ["1","1","0","0","0"],
//   ["1","1","0","0","0"],
//   ["0","0","1","0","0"],
//   ["0","0","0","1","1"]
// ]
// 输出：3

// 提示：
// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 300
// grid[i][j] 的值为 '0' 或 '1'

#include<iostream>
#include<vector>
#include<queue>
using std::queue;
using std::pair;
using std::vector;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        
    }
};


// 岛屿系列问题可以用 DFS/BFS 算法或者 Union-Find 并查集算法 来解决。
// 用 DFS 算法解决岛屿题目是最常见的，每次遇到一个岛屿中的陆地，就用 DFS 算法吧这个岛屿「淹掉」。

// 如何使用 DFS 算法遍历二维数组？你把二维数组中的每个格子看做「图」中的一个节点，这个节点和周围的四个节点连通，
// 这样二维矩阵就被抽象成了一幅网状的「图」。

// 为什么每次遇到岛屿，都要用 DFS 算法把岛屿「淹了」呢？主要是为了省事，避免维护 visited 数组。
// 图算法遍历基础 说了，遍历图是需要 visited 数组记录遍历过的节点防止走回头路。
// 因为 dfs 函数遍历到值为 0 的位置会直接返回，所以只要把经过的位置都设置为 0，就可以起到不走回头路的作用。

// 标签：DFS 算法，二维矩阵



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 深度优先遍历
// 20:56--21:06(看思路，四个方向)--21:19(不会)--21:27(看D1思路)--21:47
// dfs
#if 0
class Solution {
    int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1}; // 四个方向 逆时针(右、上、左、下) 遍历
    int count = 0;
    vector<vector<bool>> used;
    void dfs(vector<vector<char>>& grid, int row, int col) {
        if(row == grid.size() && col == grid[0].size()) {
            return;
        }
        for(int i=0; i<4; i++) {

        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        used.clear();
        count = 0;
        used = vector<vector<bool>>(grid.size(), vector<bool>(grid[0].size(), false));
        dfs(grid, 0, 0);
        return count;
    }
};
#endif

// 二维数组遍历，上下左右
class Solution_L1_M1 {
    vector<vector<bool>> used;
    // dfs作用：找到所有与其相连的土地并做上标记
    void dfs(vector<vector<char>>& grid, int i, int j) {
        // 超出索引范围
        if(i<0 || j<0 || i>=grid.size() || j>=grid[0].size()) {
            return;
        }
        // 已经遍历过
        if(used[i][j] == true) {
            return;
        }
        // 遍历的是海洋
        if(grid[i][j] == '0') {
            used[i][j] = true;
            return;
        }
        // grid[i][j]是陆地，遍历周围的四个方向(并作上标记)
        used[i][j] = true;
        dfs(grid, i-1, j);
        dfs(grid, i+1, j);
        dfs(grid, i, j+1);
        dfs(grid, i, j-1);
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        int row = grid.size();
        int col = grid[0].size();
        used = vector<vector<bool>>(row, vector<bool>(col, false));
        // 遍历所有节点，找到一个岛屿后就标记其所有土地
        for(int i=0; i<row; i++) {
            for(int j=0; j<col; j++) {
                if(grid[i][j] == '1' && used[i][j] != true) {
                    count++;
                    dfs(grid, i, j);    // 找到一个岛屿后标记其所有土地
                }
                // used[i][j] = true;  // 不写也行，dfs里也会做上标记
            }
        }
        return count;
    }
};


// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1_copy {
    // 主函数，计算岛屿数量
public:
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        int m = grid.size(), n = grid[0].size();
        // 遍历 grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    // 每发现一个岛屿，岛屿数量加一
                    res++;
                    // 然后使用 DFS 将岛屿淹了
                    dfs(grid, i, j);
                }
            }
        }
        return res;
    }

private:
    // 从 (i, j) 开始，将与之相邻的陆地都变成海水
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n) {
            // 超出索引边界
            return;
        }
        if (grid[i][j] == '0') {
            // 已经是海水了
            return;
        }
        // 将 (i, j) 变成海水
        grid[i][j] = '0';
        // 淹没上下左右的陆地
        dfs(grid, i + 1, j);
        dfs(grid, i, j + 1);
        dfs(grid, i - 1, j);
        dfs(grid, i, j - 1);
    }
};


// 隐含的终止条件
class Solution_D1_copy {
private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            if (!visited[nextx][nexty] && grid[nextx][nexty] == '1') { // 没有访问过的 同时 是陆地的
                visited[nextx][nexty] = true; 
                dfs(grid, visited, nextx, nexty);
            } 
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false)); 

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == '1') { 
                    visited[i][j] = true;
                    result++; // 遇到没访问过的陆地，+1
                    dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                }
            }
        }
        return result;
    }
};


// 加上终止条件
class Solution_D2_copy {
private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 四个方向
    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        if (visited[x][y] || grid[x][y] == '0') return; // 终止条件：访问过的节点 或者 遇到海水
        visited[x][y] = true; // 标记访问过
        for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 越界了，直接跳过
            dfs(grid, visited, nextx, nexty);
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == '1') {
                    result++; // 遇到没访问过的陆地，+1
                    dfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
                }
            }
        }
        return result;
    }
};








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 广度优先遍历

// 16:03(看题找思路)--16:18(忘记队列)--16：37(不会，看思路)
// 16:38
// 四个方向，维护一个队列
// 不少同学用广搜做这道题目的时候，超时了。 这里有一个广搜中很重要的细节：
// 根本原因是只要 加入队列就代表 走过，就需要标记，而不是从队列拿出来的时候再去标记走过。
// 如果从队列拿出节点，再去标记这个节点走过，就会发生下图所示的结果，会导致很多节点重复加入队列。
class Solution_D3_M1 {
    vector<vector<bool>> used;
    int dir[4][2] = {0, 1, 0, -1, -1, 0, 1, 0}; // 上下左右
    void bfs(vector<vector<char>>& grid, int x, int y) {
        // // 当遇到海洋或已经被标记过的
        // if(grid[x][y] == '0' || used[x][y]) {
        //     used[x][y] = true;
        //     return;
        // }
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> que;
        que.push(pair<int,int>(x, y));
        used[x][y] = true;  // 加入队列的时候就标记，防止重复加入
        while(!que.empty()) {
            pair<int, int> cur = que.front();
            que.pop();
            int cur_x = cur.first;
            int cur_y = cur.second;
            for(int i=0; i<4; i++) {
                int next_x = cur_x + dir[i][0];
                int next_y = cur_y + dir[i][1];
                // 判断索引
                if(next_x < 0 || next_y < 0 || next_x >= m || next_y >= n) continue;
                // 是海洋或者已经被标记过了
                if(grid[next_x][next_y] == '0' || used[next_x][next_y]) continue;
                // 剩下的只能是没被标记过的陆地
                // if(grid[next_x][next_y] == '1' && used[next_x][next_y])
                que.push(pair<int, int>(next_x, next_y));   // 加入队列，等这一圈处理完后再处理这一块陆地的四周（广度优先）
                used[next_x][next_y] = true;    // 加入队列的时候就标记，防止重复加入
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        used = vector<vector<bool>>(m, vector<bool>(n, false));
        int result = 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(!used[i][j] && grid[i][j] == '1') {
                    result++;
                    bfs(grid, i, j);    // 把周围的都标记上
                }
                // used[i][j] = true;   // 可以不用
            }
        }
        return result;
    }
};