// 797. 所有可能的路径
// https://leetcode.cn/problems/all-paths-from-source-to-target/
// labuladong 题解思路
// 中等
// 给你一个有 n 个节点的 有向无环图（DAG），请你找出所有从节点 0 到节点 n-1 的路径并输出（不要求按特定顺序）
//  graph[i] 是一个从节点 i 可以访问的所有节点的列表（即从节点 i 到节点 graph[i][j] 存在一条有向边）。

// 示例 1：
// 输入：graph = [[1,2],[3],[3],[]]
// 输出：[[0,1,3],[0,2,3]]
// 解释：有两条路径 0 -> 1 -> 3 和 0 -> 2 -> 3

// 示例 2：
// 输入：graph = [[4,3,1],[3,2,4],[3],[4],[]]
// 输出：[[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]

// 提示：
// n == graph.length
// 2 <= n <= 15
// 0 <= graph[i][j] < n
// graph[i][j] != i（即不存在自环）
// graph[i] 中的所有元素 互不相同
// 保证输入为 有向无环图（DAG）


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {

    }
};


// 19:58--20:11(输出空)--20:16
// 尝试深度回溯--深度优先遍历
class Solution_M1 {
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<vector<int>>& graph, int n) {  // n:当前节点号
        // 死路，或走到目标节点
        if(graph[n].size() == 0 || n == graph.size()-1) {
            if(n == graph.size()-1) result.push_back(path);
            return;
        }
        // graph[n]：当前节点的下一节点的所有可能结果
        // graph[n] = [2, 3, 4] 从当前节点能走到 2 3 4节点
        for(int i=0; i<graph[n].size(); i++) {
            path.push_back(graph[n][i]);
            backtracking(graph, graph[n][i]);   // 到下一节点继续走
            path.pop_back();
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        result.clear();
        path.clear();
        path.push_back(0);      // ***
        backtracking(graph, 0);
        return result;
    }
};


// dfs: 深度优先搜索
class Solution_D1_copy {
private:
    vector<vector<int>> result; // 收集符合条件的路径
    vector<int> path; // 0节点到终点的路径
    // x：目前遍历的节点
    // graph：存当前的图
    void dfs (vector<vector<int>>& graph, int x) {
        // 要求从节点 0 到节点 n-1 的路径并输出，所以是 graph.size() - 1
        if (x == graph.size() - 1) { // 找到符合条件的一条路径
            result.push_back(path);
            return;
        }
        for (int i = 0; i < graph[x].size(); i++) { // 遍历节点n链接的所有节点
            path.push_back(graph[x][i]); // 遍历到的节点加入到路径中来
            dfs(graph, graph[x][i]); // 进入下一层递归
            path.pop_back(); // 回溯，撤销本节点
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        path.push_back(0); // 无论什么路径已经是从0节点出发
        dfs(graph, 0); // 开始遍历
        return result;
    }
};



class Solution_L1 {
    vector<vector<int>> res;
    vector<int> path;
    // traverse
    void dfs(vector<vector<int>>& graph, int n) {
        // 添加当前节点到路径
        path.push_back(n);
        if(n == graph.size()-1) {   // 到达终点
            res.push_back(path);
            // path.pop_back()  // 如果这里直接返回，需要正确维护 path
            // return;
        }
        for(int p:graph[n]) {
            dfs(graph, p);
        }
        path.pop_back();
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        res.clear();
        path.clear();
        dfs(graph, 0);  // 从第 0 个节点开始遍历
        return res;
    }
};

