// 130. 被围绕的区域
// labuladong 题解思路
// 中等
// 给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

// 示例 1：
// 输入：board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
// 输出：[["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
// 解释：被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，
// 或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

// 示例 2：
// 输入：board = [["X"]]
// 输出：[["X"]]

// 提示：
// m == board.length
// n == board[i].length
// 1 <= m, n <= 200
// board[i][j] 为 'X' 或 'O'

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    void solve(vector<vector<char>>& board) {

    }
};

// 21:28--21:30(读题找思路)--21:49(错误)
// 实质是填充飞地，保持其余地方不变
// dfs
// 输入
// board =
// [["O","O","O"],["O","O","O"],["O","O","O"]]
// 输出
// [["O","O","O"],["O","X","O"],["O","O","O"]]
// 预期结果
// [["O","O","O"],["O","O","O"],["O","O","O"]]
class Solution_M1 {
    int m, n;
    vector<vector<bool>> used;
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    // 遍历一整个岛屿
    void dfs(vector<vector<char>>& board, int x, int y, bool rep) {
        // 超出索引范围
        if(x < 0 || y < 0 || x >= m || y >= n) return;
        // 不是 O 或 已被标记
        if(board[x][y] == 'X' || used[x][y]) return;
        // 是否替换
        if(rep) board[x][y] = 'X';
        // 标记
        used[x][y] = true;
        for(int i=0; i<4; i++) {
            dfs(board, x + dir[i][0], y + dir[i][1], rep);
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        m = board.size();
        n = board[0].size();
        used = vector<vector<bool>>(m, vector<bool>(n, false));
        // 遍历四周，做上标记，不替换
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(i == 0 || j == 0 || i == m-1 || j == n-1) {
                    if(board[i][j] == 'O' && !used[i][j]) {
                        dfs(board, i, j, false);
                    }
                }
            }
        }
        // // 遍历内部，将飞地全部替换为 'X'
        // for(int i=1; i<m-1; i++) {
        //     for(int j=1; j<n-1; j++) {
        //         if(board[i][j] == 'O' && !used[i][j]) {
        //             dfs(board, i, j, true);
        //         }
        //     }
        // }
        // 遍历内部，将没被标记的地方全部替换为 'X'
        for(int i=1; i<m-1; i++) {
            for(int j=1; j<n-1; j++) {
                if(!used[i][j] && board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};


// dfs
// 不消耗额外空间，先将周围的 O 替换成其他字符后（A）再替换回 O
// 20:41--20:53
class Solution_D1_M2 {
    int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
    int m, n;
    void dfs(vector<vector<char>>& board, int x, int y) {
        board[x][y] = 'A';
        for(int i=0; i<4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if(nextx<0 || nextx>=m || nexty<0 || nexty>=n) continue;
            if(board[nextx][nexty] == 'O') {
                dfs(board, nextx, nexty);
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        m = board.size();
        n = board[0].size();
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(i == 0 || i==m-1 || j==0 || j==n-1) {
                    if(board[i][j] == 'O') {
                        dfs(board, i, j);
                    }
                }
            }
        }

        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(board[i][j] == 'A') board[i][j] = 'O';
                if(board[i][j] == 'O') board[i][j] = 'X';
            }
        }
    }
};





// 19:50--20:04(错误)--20:28
class Solution_L1 {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();
        UF uf(m*n + 1);
        int dummy = m*n;
        // dummy 连接四周的 O
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(i==0 || i==m-1 || j==0 || j==n-1) {
                    if(board[i][j] == 'O') {    // 判断         ***
                        uf.union_(i*n+j, dummy);
                    }
                }
            }
        }
        // 将每个 O 节点同上下左右连接起来
        int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
        for(int i=1; i<m-1; i++) {
            for(int j=1; j<n-1; j++) {
                if(board[i][j] == 'O') {
                    for(int k=0; k<4; k++) {    // k            ***
                        int nx = i + dir[k][0];
                        int ny = j + dir[k][1];
                        // 不用判断 nx ny，因为在内部
                        if(board[nx][ny] == 'O') {  // 判断     ***
                            uf.union_(nx*n + ny, n*i + j);
                        }
                    }
                }
            }
        }
        // 将根节点不是 dummy 的 O 全部替换
        for(int i=1; i<m-1; i++) {
            for(int j=1; j<n-1; j++) {
                if(board[i][j] == 'O' && !uf.connected(i*n+j, dummy)) {
                    board[i][j] = 'X';
                }
            }
        }
    }

    class UF {
    private:
        int count;
        int* parent;
    public:
        UF(int n) {
            count = n;
            parent = new int[n];
            for(int i=0; i<n; i++) {
                parent[i] = i;
            }
        }
        ~UF() {
            delete[] parent;
        }
        int find(int x) {
            if(parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        // rootQ 是根节点
        void union_(int p, int q) {
            int rootP = find(p);
            int rootQ = find(q);
            if(rootP != rootQ) {
                parent[rootP] = rootQ;
                count--;
            }
        }
        bool connected(int p, int q) {
            return find(p) == find(q);  // 写成了 parent[]      ***
        }
        int count_() {
            return count;
        }
    };
};

