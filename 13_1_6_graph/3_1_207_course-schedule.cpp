// 207. 课程表
// https://leetcode.cn/problems/course-schedule
// labuladong 题解
// 思路
// 中等
// 提示
// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，
// 表示如果要学习课程 ai 则 必须 先学习课程  bi 。

// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

// 示例 1：
// 输入：numCourses = 2, prerequisites = [[1,0]]
// 输出：true
// 解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。

// 示例 2：
// 输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
// 输出：false
// 解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。

// 提示：
// 1 <= numCourses <= 2000
// 0 <= prerequisites.length <= 5000
// prerequisites[i].length == 2
// 0 <= ai, bi < numCourses
// prerequisites[i] 中的所有课程对 互不相同

#include<iostream>
#include<vector>
#include<queue>
using std::queue;
using std::vector;



class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

    }
};


// 9:50--10:50(学习函数返回vector)--11:39(ok)
// 11:39--11:47(buildGraph错误)--11:51
// 有向图 环检测 dfs onPath hasCycle
class Solution_L1_M1 {
    vector<bool> visited;
    vector<bool> onPath;
    bool hasCycle = false;
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        visited.resize(numCourses, false);
        onPath.resize(numCourses, false);
        vector<vector<int>> graph = buildGraph(numCourses, prerequisites);
        // 图中并不是所有节点都相连，所以要用一个 for 循环将所有节点都作为起点调用一次 DFS 搜索算法。
        for(int i=0; i<numCourses; i++) {
            // 遍历图中的所有节点
            traverse(graph, i);
            if(hasCycle) return false;  // 及时结束
        }
        return true;
    }
private:
    // DFS
    void traverse(vector<vector<int>>& graph, int s) {
        // 遇到环了
        if(onPath[s]) hasCycle = true;
        // 已经遍历过了或已经遇到环了
        if(visited[s] || hasCycle) return;
        // 前序遍历代码位置
        onPath[s] = true;   // 路径记录
        visited[s] = true;  // 防止重复遍历
        for(auto c:graph[s]) {  // 深度遍历
            traverse(graph, c);
        }
        onPath[s] = false;  // 路径回退
    }
    // 由条件建图
    vector<vector<int>> buildGraph(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        // for(int i=0; i<numCourses; i++)  // prerequisites大小和numCourse不同
        for(auto edge:prerequisites) {
            int from = edge[1]; // 修完 from 才能修 to
            int to = edge[0];
            graph[from].push_back(to);
        }
        return graph;
    }
};


// 13:43--14:03
// 有向图 环检测 bfs queue indegree
// 入度和出度
class Solution_L2_M2 {
    // 统计每个节点的入度
    vector<int> indegree;
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        indegree.resize(numCourses, 0);
        vector<vector<int>> graph = buildGraph(numCourses, prerequisites);
        queue<int> q;
        for(int i=0; i<numCourses; i++) {
            if(indegree[i] == 0) {
                q.push(i);  // 节点 i 没有入度，即没有依赖的节点,可以作为拓扑排序的起点，加入队列
            }
        }
        // 开始执行 BFS 循环
        // 记录遍历的节点个数
        int count = 0;
        while(!q.empty()) {
            // 弹出节点 cur，并将它指向的节点的入度减一
            int cur = q.front();
            q.pop();
            count++;    // 每处理/遍历一个节点 count++
            for(int next:graph[cur]) {
                indegree[next]--;
                if(indegree[next] == 0) {
                    q.push(next);    // 如果入度变为 0，说明 next 依赖的节点都已被遍历
                }
            }
        }
        
        // 如果所有节点都被遍历过，说明不成环
        return count == numCourses;
    }
private:
    vector<vector<int>> buildGraph(int numCourses, vector<vector<int>>&prerequisites) {
        vector<vector<int>> graph(numCourses);
        for(auto edge:prerequisites) {
            int from = edge[1];
            int to = edge[0];
            graph[from].push_back(to);
            indegree[to]++; // 统计每个节点的入度   ***
        }
        return graph;
    }
};


// 14:32--14:50
// 有向图 环检测 不能用并查集
#if 0
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        UF uf(numCourses);
        for(auto& edge:prerequisites) {
            int from = edge[1];
            int to = edge[0];
            if(uf.connected(from, to)) return false;    // 两者已经处于同一联通分量时，出现环----错误
            uf.union_(from, to);
        }
        return true;
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
                parent[x] = find(parent[x]);    // ***
            }
            return parent[x];
        }
        void union_(int x, int y) {
            int rootx = find(x);
            int rooty = find(y);
            if(rootx == rooty) return;
            parent[rooty] = rootx;
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
#endif

