// 1631. 最小体力消耗路径
// https://leetcode.cn/problems/path-with-minimum-effort
// labuladong 题解
// 思路
// 中等
// 提示
// 你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights ，其中 heights[row][col] 表示格子 (row, col) 的高度。
// 一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1) 
// （注意下标从 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动，你想要找到耗费 体力 最小的一条路径。
// 一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。
// 请你返回从左上角走到右下角的最小 体力消耗值 。

// 示例 1：
// 输入：heights = [[1,2,2],[3,8,2],[5,3,5]]
// 输出：2
// 解释：路径 [1,3,5,3,5] 连续格子的差值绝对值最大为 2 。
// 这条路径比路径 [1,2,2,2,5] 更优，因为另一条路径差值最大值为 3 。

// 示例 2：
// 输入：heights = [[1,2,3],[3,8,4],[5,3,5]]
// 输出：1
// 解释：路径 [1,2,3,4,5] 的相邻格子差值绝对值最大为 1 ，比路径 [1,3,5,3,5] 更优。

// 示例 3：
// 输入：heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
// 输出：0
// 解释：上图所示路径不需要消耗任何体力。

// 提示：
// rows == heights.length
// columns == heights[i].length
// 1 <= rows, columns <= 100
// 1 <= heights[i][j] <= 10^6

#include<iostream>
#include<vector>
#include<queue>
#include<functional>
using std::function;
using std::priority_queue;
using std::pair;
using std::vector;
using std::max;


class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {

    }
};


// 11:47--11:53
// 15:57
// 21:40--22:17--23:13(超时)--小顶堆比较函数构造错误
// 双向图，从开始节点到最大节点的最小路径差
class Solution_M1 {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        // 由矩阵建立双向图，建图时间太长
        int rows = heights.size();
        int cols = heights[0].size();
        vector<vector<pair<int, int>>> graph(rows*cols + 1);
        int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                int cur = i * cols + j + 1;
                for(int k=0; k<4; k++) {
                    int nextX = i + dir[k][0];
                    int nextY = j + dir[k][1];
                    if(nextX < 0 || nextX >= rows || nextY <0 || nextY >= cols) continue;
                    int next = nextX * cols + nextY + 1;
                    graph[cur].push_back({next, std::abs(heights[i][j] - heights[nextX][nextY])});
                }
            }
        }

        // dijkstra
        vector<int> distTo(rows*cols + 1, INT_MAX); // ***
        distTo[1] = 0;                              // ***
        // 优先级队列，小顶堆
        priority_queue<pair<int, int>, vector<pair<int, int>>, function<bool(const pair<int, int>&, const pair<int, int>&)>> pq(
            [](const pair<int, int>& a, const pair<int, int>& b) {
                return a.second > b.second; // ？？？
            }
        );
        pq.push({1, 0});                            // ***
        while(!pq.empty()) {
            pair<int, int> cur = pq.top();
            pq.pop();
            int curID = cur.first;
            int curMinDiff = cur.second;
            // 到达该节点
            if(curID == rows*cols + 1) return curMinDiff;
            // 错误路径
            if(curMinDiff > distTo[curID]) continue;    // 因为要找最小值
            // 更优路径
            for(auto& next : graph[curID]) {
                int nextID = next.first;
                // 前面路径上的最小值 与 当前节点与下一节点差值 的比较
                int nextMinDiff= std::max(distTo[curID], next.second); // ***
                if(nextMinDiff < distTo[nextID]) {
                    distTo[nextID] = nextMinDiff;
                    pq.push({nextID, nextMinDiff});
                }
            }
        }
        return distTo.back();
    }
};

// 14:53
// 不单独建图，返回相邻节点即可
class Solution_L1_M2 {
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
            neighbors.push_back({nextX, nextY});
        }
        return neighbors;
    }
    struct State {
        int x;
        int y;
        int effortFromStart;
        State(int x, int y, int e) : x(x), y(y), effortFromStart(e) { }
    };
    struct Cmp {
        bool operator()(const State& a, const State& b) {
            return a.effortFromStart > b.effortFromStart;   // ***
        }
    };
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        // 存放(0, 0)到(i, j)的最小消耗
        vector<vector<int>> effortTo(m, vector<int>(n, INT_MAX));
        effortTo[0][0] = 0;
        // 优先级队列，小顶堆
        priority_queue<State, vector<State>, Cmp> pq;
        // 从起点开始 BFS
        pq.push(State(0, 0, 0));
        while(!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            int curX = cur.x;
            int curY = cur.y;
            int curEffortFromStart = cur.effortFromStart;   // 从小顶堆中取出的都是已经参与过计算的
            // 提前找到
            if(curX == m-1 && curY == n-1) return curEffortFromStart;   // 每次都是先处理最小的，第一次到终点肯定是最省力的
            // 较差路径，不用继续走了
            if(curEffortFromStart > effortTo[curX][curY]) continue;
            // effortTo[curX][curY] = curEffortFromStart;   // 这句不用写，经过计算的都已经赋值过了
            // 较好路径
            for(auto& next : adj(heights, curX, curY)) {
                int nextX = next[0];
                int nextY = next[1];
                // 计算 cur 到 next 的损耗
                int effortToNextNode = std::max(curEffortFromStart, std::abs(heights[curX][curY] - heights[nextX][nextY]));
                // 更新 dp
                if(effortToNextNode < effortTo[nextX][nextY]) {
                    effortTo[nextX][nextY] = effortToNextNode;  // 是上面不用写的原因
                    pq.push(State(nextX, nextY, effortToNextNode));
                }
            }
        }
        return -1;  // 到不了终点
    }
};







// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1_copy {
public:
    // Dijkstra 算法，计算 (0, 0) 到 (m - 1, n - 1) 的最小体力消耗
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        // 定义：从 (0, 0) 到 (i, j) 的最小体力消耗是 effortTo[i][j]
        vector<vector<int>> effortTo(m,vector<int>(n, INT_MAX)); // dp table 初始化为正无穷
        // base case，起点到起点的最小消耗就是 0
        effortTo[0][0] = 0;

        // 优先级队列，effortFromStart 较小的排在前面
        priority_queue<State,vector<State>,Comp> pq; // 第二个参数就是自定义语法格式，详见下方
        // 从起点 (0, 0) 开始进行 BFS
        pq.push(State(0, 0, 0));

        while (!pq.empty()) {
            State curState = pq.top();
            pq.pop();
            int curX = curState.x;
            int curY = curState.y;
            int curEffortFromStart = curState.effortFromStart;

            // 到达终点提前结束
            if (curX == m - 1 && curY == n - 1) {
                return curEffortFromStart;
            }

            if (curEffortFromStart > effortTo[curX][curY]) {
                continue;
            }
            // 将 (curX, curY) 的相邻坐标装入队列
            for (auto& neighbor : adj(heights, curX, curY)) {
                int nextX = neighbor[0];
                int nextY = neighbor[1];
                // 计算从 (curX, curY) 达到 (nextX, nextY) 的消耗
                int effortToNextNode = max(
                    effortTo[curX][curY],
                    abs(heights[curX][curY] - heights[nextX][nextY])
                );
                // 更新 dp table
                if (effortTo[nextX][nextY] > effortToNextNode) {
                    effortTo[nextX][nextY] = effortToNextNode;
                    pq.push(State(nextX, nextY, effortToNextNode));
                }
            }
        }
        // 正常情况不会达到这个 return
        return -1;
    }

    // 方向数组，上下左右的坐标偏移量
    vector<vector<int>> dirs {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // 返回坐标 (x, y) 的上下左右相邻坐标
    vector<vector<int>> adj(vector<vector<int>>& matrix, int x, int y) {
        int m = matrix.size(), n = matrix[0].size();
        // 存储相邻节点
        vector<vector<int>> neighbors;
        for (auto& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            if (nx >= m || nx < 0 || ny >= n || ny < 0) {
                // 索引越界
                continue;
            }
            neighbors.push_back({nx, ny});
        }
        return neighbors;
    }

    struct State {
        // 矩阵中的一个位置
        int x, y;
        // 从起点 (0, 0) 到当前位置的最小体力消耗（距离）
        int effortFromStart;

        State(int x, int y, int effortFromStart) {
            this->x = x;
            this->y = y;
            this->effortFromStart = effortFromStart;
        }
    };

    struct Comp {
        bool operator() (State& a, State& b) {
            return a.effortFromStart > b.effortFromStart;
        }
    };
};
// 详细解析参见：
// https://labuladong.online/algo/slug.html?slug=path-with-minimum-effort
