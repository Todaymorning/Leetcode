// D:\Learning\Leetcode\Cpp\12_graph\5_130_surrounded-regions.cpp

#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {

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