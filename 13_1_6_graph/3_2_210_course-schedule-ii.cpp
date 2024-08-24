// 210. 课程表 II
// https://leetcode.cn/problems/course-schedule-ii
// labuladong 题解
// 思路
// 中等
// 提示
// 现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。
// 给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。
// 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
// 返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。
// 如果不可能完成所有课程，返回 一个空数组 。

// 示例 1：
// 输入：numCourses = 2, prerequisites = [[1,0]]
// 输出：[0,1]
// 解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。

// 示例 2：
// 输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
// 输出：[0,2,1,3]
// 解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
// 因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。

// 示例 3：
// 输入：numCourses = 1, prerequisites = []
// 输出：[0]

// 提示：
// 1 <= numCourses <= 2000
// 0 <= prerequisites.length <= numCourses * (numCourses - 1)
// prerequisites[i].length == 2
// 0 <= ai, bi < numCourses
// ai != bi
// 所有 [ai, bi] 互不相同


// 13:08
// 有点像多个多叉树的后序遍历

#include<iostream>
#include<vector>
#include<queue>
using std::queue;
using std::vector;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {

    }
};


// 13:15--13:28
// 拓扑排序 dfs
// 那么为什么后序遍历的反转结果就是拓扑排序呢？
// 二叉树的后序遍历是什么时候？遍历完左右子树之后才会执行后序遍历位置的代码。
// 换句话说，当左右子树的节点都被装到结果列表里面了，根节点才会被装进去。
class Solution_L1_M1 {
    vector<bool> onPath;
    vector<bool> visited;
    bool hasCycle;
    vector<int> result; // 存放结果
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        onPath.resize(numCourses, false);
        visited.resize(numCourses, false);
        hasCycle = false;
        vector<vector<int>> graph = buildGraph(numCourses, prerequisites);
        for(int i=0; i<numCourses; i++) {
            traverse(graph, i);
        }
        if(hasCycle) result.clear();
        return result;
    }
private:
    void traverse(vector<vector<int>>& graph, int s) {
        if(onPath[s]) hasCycle = true;
        if(hasCycle || visited[s]) return;
        onPath[s] = true;
        visited[s] = true;
        for(auto c:graph[s]) {
            traverse(graph, c); // dfs
        }
        // 后序位置
        // 1-->2-->3，从后往前遍历（子节点是被依赖的课程），遍历到最底层
        // 最低层的是优先级最高的课程，先push_back后再push_back之前的课程
        result.push_back(s);                                        // ***
        onPath[s] = false;
    }
    vector<vector<int>> buildGraph(int numCourses, vector<vector<int>>& prerequistes) {
        vector<vector<int>> graph(numCourses);
        for(auto edge:prerequistes) {
            int from = edge[1];
            int to = edge[0];
            // graph[from].push_back(to);   // 根节点是被依赖的课程
            graph[to].push_back(from);  // 子节点是被依赖的课程         // ***
        }
        return graph;
    }
};


// 14:08
// 拓扑排序 bfs
class Solution_L2_M2 {
    vector<int> indegree;
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        indegree.resize(numCourses, 0);
        vector<vector<int>> graph = buildGraph(numCourses, prerequisites);
        queue<int> q;
        // 入度为 0 的加入队列
        for(int i=0; i<numCourses; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> result;
        int count = 0;
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            // 将入度为 0 的节点加入 "没有依赖"
            count++;
            result.push_back(cur);          // ***
            for(auto next:graph[cur]) {
                indegree[next]--;
                if(indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        if(count != numCourses) result.clear(); // 有环
        return result;
    }
    vector<vector<int>> buildGraph(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        for(auto edge:prerequisites) {
            int from = edge[1];
            int to = edge[0];
            graph[from].push_back(to);
            indegree[to]++;
        }
        return graph;
    }
};
