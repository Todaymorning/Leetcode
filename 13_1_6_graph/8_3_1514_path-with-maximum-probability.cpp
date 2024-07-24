// 1514. 概率最大的路径
// https://leetcode.cn/problems/path-with-maximum-probability
// labuladong 题解
// 思路
// 中等
// 相关标签
// 相关企业
// 提示
// 给你一个由 n 个节点（下标从 0 开始）组成的无向加权图，该图由一个描述边的列表组成，
// 其中 edges[i] = [a, b] 表示连接节点 a 和 b 的一条无向边，且该边遍历成功的概率为 succProb[i] 。
// 指定两个节点分别作为起点 start 和终点 end ，请你找出从起点到终点成功概率最大的路径，并返回其成功概率。
// 如果不存在从 start 到 end 的路径，请 返回 0 。只要答案与标准答案的误差不超过 1e-5 ，就会被视作正确答案。

// 示例 1：
// 输入：n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
// 输出：0.25000
// 解释：从起点到终点有两条路径，其中一条的成功概率为 0.2 ，而另一条为 0.5 * 0.5 = 0.25

// 示例 2：
// 输入：n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
// 输出：0.30000

// 示例 3：
// 输入：n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
// 输出：0.00000
// 解释：节点 0 和 节点 2 之间不存在路径

// 提示：
// 2 <= n <= 10^4
// 0 <= start, end < n
// start != end
// 0 <= a, b < n
// a != b
// 0 <= succProb.length == edges.length <= 2*10^4
// 0 <= succProb[i] <= 1
// 每两个节点之间最多有一条边

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
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        
    }
};



// 17:01--17:03--17:10(吃饭)--18:03--18:20
// 概率相乘，求路径上概率最大值
class Solution {
    // 某个节点到 id
    struct State {
        int id;
        double curSuccProb;
        State(int id, double succProb) : id(id), curSuccProb(succProb) {}
    };
    struct Cmp {
        bool operator()(const State& a, const State& b) {
            return a.curSuccProb < b.curSuccProb;   // 大顶堆
        }
    };
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        // 建图
        int num = edges.size();
        vector<vector<State>> graph(n);
        for(int i=0; i<edges.size(); i++) {
            int from = edges[i][0];
            int to = edges[i][1];
            double prob = succProb[i];
            graph[from].push_back(State(to, prob)); // 双向
            graph[to].push_back(State(from, prob));
        }

        vector<double> probTo(n, INT_MIN);
        probTo[start_node] = 1;
        // 大顶堆，概率大的优先
        priority_queue<State, vector<State>, Cmp> pq;
        pq.push(State(start_node, 1));
        while(!pq.empty()) {
            State cur = pq.top();
            pq.pop();
            int curID = cur.id;
            double curSuccProb = cur.curSuccProb;
            // 到达终点
            if(curID == end_node) return curSuccProb;
            // 已经有一条概率更大的路径到达 curNode 节点了
            if(curSuccProb < probTo[curID]) continue;
            for(auto& next : graph[curID]) {
                int nextID = next.id;
                double probToNext = probTo[curID] * next.curSuccProb;   // 概率相乘
                if(probToNext > probTo[nextID]) {
                    probTo[nextID] = probToNext;
                    pq.push(State(nextID, probToNext));
                }
            }
        }
        return 0.0;
    }
};