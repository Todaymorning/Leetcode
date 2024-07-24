// 886. 可能的二分法
// https://leetcode.cn/problems/possible-bipartition
// labuladong 题解
// 思路
// 中等
// 相关标签
// 相关企业
// 给定一组 n 人（编号为 1, 2, ..., n）， 我们想把每个人分进任意大小的两组。每个人都可能不喜欢其他人，那么他们不应该属于同一组。

// 给定整数 n 和数组 dislikes ，其中 dislikes[i] = [ai, bi] ，表示不允许将编号为 ai 和  bi 的人归入同一组。当可以用这种方法将所有人分进两组时，返回 true；否则返回 false。

// 示例 1：
// 输入：n = 4, dislikes = [[1,2],[1,3],[2,4]]
// 输出：true
// 解释：group1 [1,4], group2 [2,3]

// 示例 2：
// 输入：n = 3, dislikes = [[1,2],[1,3],[2,3]]
// 输出：false

// 示例 3：
// 输入：n = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
// 输出：false

// 提示：
// 1 <= n <= 2000
// 0 <= dislikes.length <= 10^4
// dislikes[i].length == 2
// 1 <= dislikes[i][j] <= n
// ai < bi
// dislikes 中每一组都 不同


#include<iostream>
#include<vector>
#include<queue>
using std::queue;
using std::vector;

class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {

    }
};


// 11:36
// 16:06--16:09(看题找思路)--16:24
// 先建图，后判断是否是二分图
// dfs
class Solution_L1_M1 {
    vector<bool> visited;
    vector<bool> color;
    bool ok;
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        // 这里的节点没有 0                 ***
        visited.resize(n + 1, false);
        color.resize(n + 1, false);
        ok = true;
        // 构建双向图
        vector<vector<int>> graph = buildGraph(n, dislikes);
        // 二分图判断
        for(int i=1; i<=n; i++) {
            if(!visited[i] && ok) {
                traverse(graph, i);
            }
        }
        return ok;
    }
private:
    // dfs
    void traverse(vector<vector<int>>& graph, int s) {
        // if(visited[s])  return;
        visited[s] = true;
        for(auto next:graph[s]) {
            // 下一节点没被访问，染上与当前节点相反的颜色后深度遍历
            if(!visited[next]) {
                color[next] = !color[s];
                traverse(graph, next);
            }
            else {
                // 下一节点被访问过了，判断是否颜色相反
                if(color[next] == color[s]) {
                    ok = false;
                }
            }
        }
    }
    vector<vector<int>> buildGraph(int n, vector<vector<int>>& dislikes) {
        vector<vector<int>> graph(n + 1); // 图中没有 0, 1~n        ***
        for(auto edge:dislikes) {
            int from = edge[1]; // 之前表示依赖关系单向图，这里是相互关系，双向图
            int to = edge[0];
            graph[from].push_back(to);                              // ***
            graph[to].push_back(from);
        }
        return graph;
    }
};


// bfs
class Solution_M2 {
    vector<bool> visited;
    vector<bool> color;
    bool ok;
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        visited.resize(n + 1, false);
        color.resize(n + 1, false);
        ok = true;
        // 构建双向图
        vector<vector<int>> graph = buildGraph(n, dislikes);
        // 二分图判断
        for(int i=1; i<=n; i++) {
            if(!visited[i] && ok) {
                traverse(graph, i);
            }
        }
        return ok;
    }
private:
    // bfs
    void traverse(vector<vector<int>>& graph, int s) {
        queue<int> q;
        q.push(s);
        visited[s] = true;  // 加入就马上标记，而不是处理后才标记，防止重复加入队列
        while(!q.empty() && ok) {
            int cur = q.front();
            q.pop();
            for(auto next:graph[cur]) {
                if(!visited[next]) {
                    color[next] = !color[cur];
                    q.push(next);
                    visited[next] = true;
                }
                else {
                    if(color[next] == color[cur]) {
                        ok = false;
                    }
                }
            }
        }
    }
    vector<vector<int>> buildGraph(int n, vector<vector<int>>& dislikes) {
        vector<vector<int>> graph(n + 1); // 图中没有 0, 1~n        ***
        for(auto edge:dislikes) {
            int from = edge[1]; // 之前表示依赖关系单向图，这里是相互关系，双向图
            int to = edge[0];
            graph[from].push_back(to);
            graph[to].push_back(from);
        }
        return graph;
    }
};