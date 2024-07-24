// D:\Learning\Leetcode\Cpp\12_graph\1_797_all-paths-from-source-to-target.cpp

#include<iostream>
#include<vector>
using std::vector;


// 9:55--10:02
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