// 785. 判断二分图
// https://leetcode.cn/problems/is-graph-bipartite/
// labuladong 题解
// 思路
// 中等
// 存在一个 无向图 ，图中有 n 个节点。其中每个节点都有一个介于 0 到 n - 1 之间的唯一编号。给你一个二维数组 graph ，
// 其中 graph[u] 是一个节点数组，由节点 u 的邻接节点组成。形式上，对于 graph[u] 中的每个 v ，都存在一条位于节点 u 
// 和节点 v 之间的无向边。该无向图同时具有以下属性：
// 不存在自环（graph[u] 不包含 u）。
// 不存在平行边（graph[u] 不包含重复值）。
// 如果 v 在 graph[u] 内，那么 u 也应该在 graph[v] 内（该图是无向图）
// 这个图可能不是连通图，也就是说两个节点 u 和 v 之间可能不存在一条连通彼此的路径。
// 二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B ，并使图中的每一条边的两个节点一个来自 A 集合，
// 一个来自 B 集合，就将这个图称为 二分图 。
// 如果图是二分图，返回 true ；否则，返回 false 。

// 示例 1：
// 输入：graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
// 输出：false
// 解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。

// 示例 2：
// 输入：graph = [[1,3],[0,2],[1,3],[0,2]]
// 输出：true
// 解释：可以将节点分成两组: {0, 2} 和 {1, 3} 。

// 提示：
// graph.length == n
// 1 <= n <= 100
// 0 <= graph[u].length < n
// 0 <= graph[u][i] <= n - 1
// graph[u] 不会包含 u
// graph[u] 的所有值 互不相同
// 如果 graph[u] 包含 v，那么 graph[v] 也会包含 u

#include<iostream>
#include<vector>
#include<queue>
using std::queue;
using std::vector;


class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {

    }
};


// 16:41--16:52(错误)
// 输入
// graph =
// [[1],[0,3],[3],[1,2]]
// 输出
// false
// 预期结果
// true
// dfs
class Solution_L1_M1 {
    vector<bool> visited;
    vector<bool> color;     // 两种颜色
    bool ok;
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        visited.resize(n, false);
        color.resize(n, false);
        ok = true;
        // 图可能不连通（可能存在多个子图），需要遍历每个节点进行 dfs
        for(int i=0; i<n; i++) {
            // if(!visited[i])      // 加上这句后可以保证进入traverse时 visited[i] = false, traverse中也有判断visited的语句，此时traverse中有句语句可以不要
            traverse(graph, i);
        }
        return ok;
    }
    // dfs
    void traverse(vector<vector<int>>& graph, int s) {
        if(visited[s]) return;  // 上面有判断后，这句可以不要
        if(!ok) return;
        visited[s] = true;
        for(auto next:graph[s]) {   // 下一节点可能被访问过也可能没被访问过
            if(visited[next]) {
                // 访问过了，需要判断相邻节点的颜色是否相反
                if(color[next] != color[s]) {
                    continue;
                }
                else {
                    ok = false;
                }
            }
            else {
                // 没有访问过，需要染成与s相反的颜色
                color[next] = !color[s];
                // 继续遍历
                traverse(graph, next);              // ***
            }
        }
    }
};



// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码不保证正确性，仅供参考。如有疑惑，可以参照我写的 java 代码对比查看。

class Solution_L1_copy {
private:
    // 记录图是否符合二分图性质
    bool ok = true;
    // 记录图中节点的颜色，false 和 true 代表两种不同颜色
    vector<bool> color;
    // 记录图中节点是否被访问过
    vector<bool> visited;

public:
    // 主函数，输入邻接表，判断是否是二分图
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        color.resize(n);
        visited.resize(n);
        // 因为图不一定是联通的，可能存在多个子图
        // 所以要把每个节点都作为起点进行一次遍历
        // 如果发现任何一个子图不是二分图，整幅图都不算二分图
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                traverse(graph, v);
            }
        }
        return ok;
    }

    // DFS 遍历框架
    void traverse(vector<vector<int>>& graph, int v) {
        // 如果已经确定不是二分图了，就不用浪费时间再递归遍历了
        if (!ok) return;

        visited[v] = true;
        for (int w : graph[v]) {
            if (!visited[w]) {
                // 相邻节点 w 没有被访问过
                // 那么应该给节点 w 涂上和节点 v 不同的颜色
                color[w] = !color[v];
                // 继续遍历 w
                traverse(graph, w);
            } else {
                // 相邻节点 w 已经被访问过
                // 根据 v 和 w 的颜色判断是否是二分图
                if (color[w] == color[v]) {
                    // 若相同，则此图不是二分图
                    ok = false;
                    return;
                }
            }
        }
    }
};



// 11:12--11:25
// bfs
class Solution {
    vector<bool> visited;
    vector<bool> color;
    bool ok;
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        visited.resize(n, false);
        color.resize(n, false);
        ok = true;
        for(int i=0; i<n; i++) {
            if(!visited[i] && ok) {
                traverse(graph, i);
            }
        }
        return ok;
    }
private:
    // bfs 借助 queue 不用递归
    void traverse(vector<vector<int>>& graph, int s) {
        queue<int> q;
        q.push(s);
        visited[s] = true;          // 加入队列就标记，防止重复加入     ***
        // 遍历所有节点，当遇到冲突的时候不用继续遍历了，直接跳出循环
        while(!q.empty() && ok) {
            // 队列中都是一层一层地处理，即 bfs
            int cur = q.front();
            q.pop();
            // visited[cur] = true;
            for(auto next:graph[cur]) {
                if(visited[next]) {
                    // 相邻节点已经被遍历过了，判断颜色是否相同
                    if(color[cur] == color[next]) {
                        ok = false; // 颜色相同，不能二分
                        break;
                    }
                }
                else {
                    // 相邻节点未被遍历，赋予颜色后加入队列
                    color[next] = !color[cur];
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
    }
};