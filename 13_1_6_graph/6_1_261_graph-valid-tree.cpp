// 所有可能的生成树中，权重和最小的那棵生成树就叫「最小生成树」。
// 一般来说，我们都是在无向加权图中计算最小生成树的，所以使用最小生成树算法的现实场景中，图的边权重一般代表成本、距离这样的标量。

// 261. 以图判树
// https://leetcode.cn/problems/graph-valid-tree
// 中等
// 相关标签
// 相关企业
// 提示
// 给定编号从 0 到 n - 1 的 n 个结点。给定一个整数 n 和一个 edges 列表，其中 edges[i] = [ai, bi] 表示图中节点 ai 和 bi 之间存在一条无向边。
// 如果这些边能够形成一个合法有效的树结构，则返回 true ，否则返回 false 。

// 示例 1：
// 输入: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
// 输出: true

// 示例 2:
// 输入: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
// 输出: false

// 提示：
//     1 <= n <= 2000
//     0 <= edges.length <= 5000
//     edges[i].length == 2
//     0 <= ai, bi < n
//     ai != bi
//     不存在自循环或重复的边


#include<iostream>
#include<vector>
#include<queue>
using std::vector;
using std::queue;
// using namespace std;

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {

    }
};

// 10:44--10:56
// 判断有环：两个节点在同一联通分量中
// 而判断两个节点是否连通（是否在同一个连通分量中）就是 Union-Find 算法的拿手绝活
// 无向图 判断树 并查集
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        UF uf(n);
        // 遍历所有边，将组成边的两个节点进行连接
        for(auto& edge : edges) {
            int x = edge[0];
            int y = edge[1];
            // 若两个节点已经在同一连通分量中，会产生环
            if(uf.connected(x, y)) {
                return false;
            }
            // 这条边不会产生环，可以是树的一部分
            uf.union_(x, y);
        }
        // 要保证最后只形成了一棵树，即只有一个连通分量
        return uf.count_() == 1;
    }

    class UF {
    private:
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


// 11:21--11:35(不应该加入节点就count++)--11:41
// 无向图 判断树 bfs queue indegree
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // 特殊情况                         // ***
        if(edges.size() != n -  1) return false;
        if(n == 1) return true;

        // 构建双向图
        vector<int> indegree(n, 0);
        vector<vector<int>> graph(n);
        for(auto& edge : edges) {
            int from = edge[1];
            int to = edge[0];
            graph[from].push_back(to);
            indegree[to]++;
            graph[to].push_back(from);
            indegree[from]++;
        }
        

        queue<int> q;
        // 入度为 1 的加入队列
        for(int i=0; i<n; i++) {
            if(indegree[i] == 1) {
                q.push(i);
            }
        }
        // 开始遍历
        int count = 0;                      // ***
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            count++;    // 每处理一个节点    // ***
            for(auto& next : graph[cur]) {
                indegree[next]--;
                if(indegree[next] == 1) {
                    q.push(next);
                    // count++;
                }
            }
        }
        return count == n;  // 完整遍历，如果没有完整遍历，说明存在环或独立节点
    }
};


// 11:46--12:08
// 无向图 判断树 dfs onPath hasCycle
class Solution {
    vector<bool> visited;
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        // 特殊情况                         // ***
        if(edges.size() != n -  1) return false;
        if(n == 1) return true;

        visited.resize(n, false);

        // 构建双向图
        vector<vector<int>> graph(n);
        for(auto& edge : edges) {
            int from = edge[1];
            int to = edge[0];
            graph[from].push_back(to);
            graph[to].push_back(from);
        }

        // 随便遍历一个节点，如果这个图是树的话，从这个节点可以通向其余任何节点（双向）
        traverse(graph, 0);                 // ***
        for(int i=0; i<n; i++) {
            if(!visited[i]) return false;
        }
        return true;
    }
    // dfs
    void traverse(vector<vector<int>>& graph, int s) {
        if(visited[s]) return;
        visited[s] = true;
        for(auto& next : graph[s]) {
            traverse(graph, next);
        }
    }
};