// 1584. 连接所有点的最小费用
// https://leetcode.cn/problems/min-cost-to-connect-all-points
// labuladong 题解
// 思路
// 中等
// 相关标签
// 相关企业
// 提示
// 给你一个 points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。
// 连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。
// 请你返回将所有点连接的最小总费用。只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。

// 示例 1：
// 输入：points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// 输出：20
// 解释：
// 我们可以按照上图所示连接所有点得到最小总费用，总费用为 20 。
// 注意到任意两个点之间只有唯一一条路径互相到达。

// 示例 2：
// 输入：points = [[3,12],[-2,5],[-4,1]]
// 输出：18

// 示例 3：
// 输入：points = [[0,0],[1,1],[1,0],[-1,1]]
// 输出：4

// 示例 4：
// 输入：points = [[-1000000,-1000000],[1000000,1000000]]
// 输出：4000000

// 示例 5：
// 输入：points = [[0,0]]
// 输出：0

// 提示：
// 1 <= points.length <= 1000
// -10^6 <= xi, yi <= 10^6
// 所有点 (xi, yi) 两两不同。


#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using std::priority_queue;
using std::sort;
using std::abs;
using std::vector;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {

    }
};

// 16:42--16:57
// 将所有点连接
// 最小生成树 Kruskal
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        // 生成所有边和权重
        vector<vector<int>> edges;
        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {  // j++
                edges.push_back({i, j, abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])}); // -
            }
        }
        // 按权重升序排列
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a.back() < b.back(); // 升序排列
        });

        UF uf(n);
        int total = 0;
        for(auto & edge : edges) {
            int from = edge[0];
            int to = edge[1];
            int dist = edge[2]; // 2 3
            if(uf.connected(from, to)) continue;    // 跳过成环的边
            uf.union_(from, to);
            total += dist;
        }
        return total;
    }
    class UF {
        int count;
        vector<int> parent;
    public:
        UF(int n) {
            count = n;
            parent.resize(n);
            for(int i=0; i<n; i++) {
                parent[i] = i;
            }
        }
        int find(int x) {
            if(parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        void union_(int x, int y) {
            int rootx = find(x);
            int rooty = find(y);
            if(rootx == rooty) return;
            parent[rootx] = rooty;
            count--;
        }
        bool connected(int x, int y) {
            return find(x) == find(y);
        }
        int count_() {
            return count;
        }
    };
};


// 14:23-15:58
// Prim 最小生成树
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        // 构造无向图
        int n = points.size();
        vector<vector<vector<int>>> graph(n);
        for(int i=0; i<n; i++) {    // 给节点一个编号
            for(int j=i+1; j<n; j++) {
                int xi = points[i][0], yi = points[i][1];
                int xj = points[j][0], yj = points[j][1];
                int weight = abs(xi - xj) + abs(yi - yj);
                graph[i].push_back({i, j, weight});
                graph[j].push_back({j, i, weight});
            }
        }
        Prim prim(n, graph);
        return prim.weightSum_();
    }
    class Prim {
    private:
        vector<vector<vector<int>>>& m_graph;
        vector<bool> m_visited;
        vector<int> m_parent;
        vector<int> m_weight;
        int weightSum;
        struct Cmp {
            bool operator()(const vector<int>& a, const vector<int>& b) {
                return a.back() > b.back();
            }
        };
        priority_queue<vector<int>, vector<vector<int>>, Cmp> pq;
    public:
        Prim(int n, vector<vector<vector<int>>>& graph) : m_graph(graph) {
            m_visited.resize(n, false);
            m_parent.resize(n, -1);
            m_weight.resize(n, INT_MAX);
            weightSum = 0;
            m_visited[0] = true;
            cut(0);
            while(!pq.empty()) {
                auto cur = pq.top();
                pq.pop();
                int from = cur[0], to = cur[1], weight = cur[2];
                if(m_visited[to]) continue;
                m_visited[to] = true;
                m_parent[to] = from;
                m_weight[to] = weight;
                weightSum += weight;
                cut(to);
            }
        }
        void cut(int s) {
            // 与 s 相邻的所有边和节点
            for(auto& next : m_graph[s]) {
                int from = next[0], to = next[1], weight = next[1];
                if(m_visited[to]) continue;
                pq.push(next);
            }
        }
        bool allConnected() {
            for(auto t:m_visited) {
                if(!t) return false;
            }
            return true;
        }
        int weightSum_() {
            return weightSum;
        }
    };
};