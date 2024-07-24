// https://leetcode.cn/problems/longest-increasing-subsequence
// 300. 最长递增子序列
// labuladong 题解
// 思路
// 已解答
// 中等



#include<iostream>
#include<vector>
#include<string>
#include<queue>
using namespace std;


// 四个方向
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
// 返回矩阵中(x, y)的相邻坐标
vector<vector<int>> adj(vector<vector<int>>& matrix, int x, int y) {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> neighbors;
    for(int i=0; i<4; i++) {
        int nextX = x + dir[i][0];
        int nextY = y + dir[i][1];
        if(nextX<0 || nextX>=m || nextY<0 || nextY>=n) continue;
        if(matrix[nextX][nextY] == INT_MAX) continue; // 阻塞 ***
        neighbors.push_back({nextX, nextY});
    }
    return neighbors;
}
struct State {
    int x;
    int y;
    int effortFromStart;
    bool is_checked;    // ***
    State(int x, int y, int e, int c) : x(x), y(y), effortFromStart(e), is_checked(c){ }
};
struct Cmp {
    bool operator()(const State& a, const State& b) {
        return a.effortFromStart > b.effortFromStart;
    }
};


int main() {
    // 读取数据，存放到 grip 中
    int M, N;
    cin >> M >> N;
    pair<int, int> start, end;  // 存放起点和终点的坐标
    vector<vector<int>> grip(M, vector<int>(N));
    vector<vector<bool>> is_check(M, vector<bool>(N, false));
    for(int i=0; i<M; i++) {
        string temp;
        cin >> temp;
        int idx = 0;
        for(int j=0; j<temp.size(); j++) {
            char cur = temp[j];
            if(cur == ' ') continue;
            if(cur == 'S') {
                grip[i][idx++] = 0; // 起点
                start = {i, idx - 1};
            }
            else if(cur == 'E') {
                grip[i][idx++] = 0; // 终点
                end = {i, idx - 1};
            }
            else if(cur == 'B') {
                grip[i][idx++] = INT_MAX;   // 阻塞点
            }
            else if(cur == 'C') {
                grip[i][idx++] = 0;        // 检查点
                is_check[i][idx-1] = true;
            }
            else {
                int n = 0;
                while(isdigit(temp[j])) {
                    n = n * 10 + (temp[j] - '0');
                    j++;
                }
                grip[i][idx++] = n;         // 常规站点
            }
        }
    }

    // 存放起点 (start.first, start.second) 到 (i, j) 的最小消耗
    vector<vector<int>> effortTo(M, vector<int>(N, INT_MAX));
    effortTo[start.first][start.second] = 0;
    // 优先级队列，小顶堆 ***
    priority_queue<State, vector<State>, Cmp> pq;
    // 从起点开始 BFS ***
    pq.push(State(start.first, start.second, 0, false));
    while(!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        int curX = cur.x;
        int curY = cur.y;
        int curEffortFromStart = cur.effortFromStart;   // 从小顶堆中取出的都是已经参与过计算的
        bool cur_is_checked = cur.is_checked;
        // 提前找到 ***
        if(curX == end.first && curY == end.second && cur_is_checked) cout << curEffortFromStart;   // 每次都是先处理最小的，第一次到终点肯定是最省力的
        // 较差路径，不用继续走了 ***
        if(!cur_is_checked && curEffortFromStart > effortTo[curX][curY]) continue;
        // 较好路径
        for(auto& next : adj(grip, curX, curY)) {
            int nextX = next[0];
            int nextY = next[1];
            // 计算 cur 到 next 的损耗 ***
            int effortToNextNode = curEffortFromStart + grip[curX][curY];
            // 遇到更小的路径 或 之前没经过检查站现在正在经过 ***
            if(effortToNextNode < effortTo[nextX][nextY] || (!cur_is_checked && is_check[curX][curY])) {
                effortTo[nextX][nextY] = effortToNextNode;
                pq.push(State(nextX, nextY, effortToNextNode, cur_is_checked || is_check[curX][curY])); // ***
            }
        }
    }
    // 不能走到终点时输出 -1;
    cout << (effortTo[end.first][end.second] == INT_MAX ? -1 : effortTo[end.first][end.second]);
    return 0;
}