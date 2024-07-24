// https://leetcode.cn/problems/number-of-islands/description/
// 200. 岛屿数量

#include<iostream>
#include<vector>
#include<queue>
using std::queue;
using std::pair;
using std::vector;


// 2024年4月28日
// 11:09--11:24
// 深度优先遍历 dfs
class Solution {
    int result = 0;
    int m, n;
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    vector<vector<bool>> visited;
    void dfs(const vector<vector<char>>& grid, int x, int y) {
        if(visited[x][y]) return;
        visited[x][y] = true;
        for(int i=0; i<4; i++) {
            int next_x = x + dir[i][0];
            int next_y = y + dir[i][1];
            if(next_x < 0 || next_y < 0 || next_x >= m || next_y >= n || grid[next_x][next_y] == '0') continue;
            dfs(grid, next_x, next_y);
        }

    }
public:
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size(); 
        n = grid[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(!visited[i][j] && grid[i][j] == '1') {
                    result++;
                    dfs(grid, i, j);
                }
            }
        }
        return result;
    }
};


// 2024年4月28日
// 11:31--11:42
// 广度优先遍历 bfs
class Solution {
    int m;
    int n;
    vector<vector<bool>> visited;
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    void bfs(const vector<vector<char>>& grid, int x, int y) {
        queue<pair<int, int>> q;
        q.push({x, y});
        visited[x][y] = true;
        while(!q.empty()) {
            pair<int, int> cur = q.front();
            x = cur.first;  // ***
            y = cur.second; // 忘了更新
            q.pop();
            for(int i=0; i<4; i++) {
                int next_x = x + dir[i][0];
                int next_y = y + dir[i][1];
                if(next_x < 0 || next_x >= m || next_y < 0 || next_y >= n) continue;    //  = 号
                if(grid[next_x][next_y] == '0' || visited[next_x][next_y]) continue;
                q.push({next_x, next_y});
                visited[next_x][next_y] = true;
            }
        }
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        int result = 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(!visited[i][j] && grid[i][j] == '1') {
                    result++;
                    bfs(grid, i, j);
                }
            }
        }
        return result;
    }
};
