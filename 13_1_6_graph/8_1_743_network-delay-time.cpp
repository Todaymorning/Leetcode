// 743. 网络延迟时间
// https://leetcode.cn/problems/network-delay-time
// labuladong 题解
// 思路
// 中等
// 提示
// 有 n 个网络节点，标记为 1 到 n。
// 给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，
// 其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。
// 现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。

// 示例 1：
// 输入：times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// 输出：2

// 示例 2：
// 输入：times = [[1,2,1]], n = 2, k = 1
// 输出：1

// 示例 3：
// 输入：times = [[1,2,1]], n = 2, k = 2
// 输出：-1

// 提示：
// 1 <= k <= n <= 100
// 1 <= times.length <= 6000
// times[i].length == 3
// 1 <= ui, vi <= n
// ui != vi
// 0 <= wi <= 100
// 所有 (ui, vi) 对都 互不相同（即，不含重复边）

#include<iostream>
#include<vector>
#include<queue>
#include<functional>    // function
// #include<algorithm>
using std::function;
using std::max;
using std::vector;
using std::priority_queue;
using std::pair;
using std::greater;


class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

    }
};


// 9:30--10:41--10:53
// graph 和 pq 中的 pair<int, int> 不统一
class Solution_L1_M1 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 建图
        vector<vector<pair<int, int>>> graph(n + 1);
        for(auto& edge:times) {
            int from = edge[0];
            int to = edge[1];
            int time = edge[2];
            graph[from].push_back({to, time});  // ***
        }
        // 启动 dijkstra 算法计算以节点 k 为起点到其他节点的最短路径
        vector<int> disTo = dijkstra(graph, n, k);
        // 找到最长的那一条最短路径
        int res = 0;
        for(int i=1; i<=n; i++) {               // ***
            if(disTo[i] == INT_MAX) return -1;
            res = std::max(res, disTo[i]);
        }
        return res;
    }
private:
    vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int n, int start) {    // 起点，图，节点数
        vector<int> distTo(n+1, INT_MAX);    // 节点编号从 1 开始
        distTo[start] = 0;  // start到start距离为 0
        // 小顶堆
        // pair<int, int> 存放 <curDistFromStart, id>
        // 先按第一个数排序，第一个数相同时按第二个数排序 >
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, start});                    // ***
        while(!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            // auto [id, curDistFromStart] = pq.top();
            int curID = cur.second;
            int curDistFromStart = cur.first;
            // 当前路径不是最好
            if(curDistFromStart > distTo[curID]) {
                continue;
            }
            // 有更好的路径，将符合条件的节点加入优先级队列
            for(auto next:graph[curID]) {
                // 计算当前路径下从起点到 next 的路径
                int nextID = next.first;
                int nextDistFromStart = distTo[curID] + next.second;
                // 更新 dp 加入当前节点
                if(nextDistFromStart < distTo[nextID]) {
                    distTo[nextID] = nextDistFromStart;
                    pq.push({nextDistFromStart, nextID});
                }
            }
        }
        return distTo;
    }
};



// 构造优先级队列的方法
#if 0
// 1. 自带
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

// 2. 使用 lambda 函数作为比较器
bool MyComparator = [](const pair<int, int>& a, const pair<int, int>& b) {
    if(a.first == b.first) {
        return a.second > b.second;
    } else {
        return a.first > b.first;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(MyComparator)> pq2(MyComparator);

// 3. 使用 function
priority_queue<pair<int, int>, vector<pair<int, int>>, function<bool (const pair<int, int>& a, const pair<int, int>& b)>> pq (
    [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
)

// 4. 自定义比较器类class/struct--重载()
class MyComparator2 {
public:
    bool operator() (const pair<int, int>& a, const pair<int, int>&b) {
        if(a.first == b.first) {
            return a.second > b.second;
        } else {
            return a.first > b.first;
        }
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, MyComparator2> pq3;

// 数据结构定义和运算符重载 >
struct node {
    int to_index;
    int weight;
    node(int to, int w) : to_index(to), weight(w) {}
    bool operator>(const node& other) const{
        return weight > other.weight;
    }
};
priority_queue<node, vector<node>, greater<node>> pq;



#endif


// 10:54--11:10--11:28
// 统一 pair<int,int> <id, time>
class Solution_L1_M2 {
public:
    int networkDelayTime (vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph (n + 1);    // 1~n
        for (auto& edge:times) {
            int from = edge [0];
            int to = edge [1];
            int weight = edge [2];
            graph [from].push_back ({to, weight});
        }
        vector<int> distTo = fun (graph, n, k);
        int res = 0;
        for (int i=1; i<distTo.size (); i++) {
            if (distTo [i] == INT_MAX) return -1;
            res = std::max (res, distTo [i]);
        }
        return res;
    }
    vector<int> fun (vector<vector<pair<int, int>>>& graph, int n, int start) {
        vector<int> distTo (n + 1, INT_MAX);
        distTo [start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, 
            function<bool (const pair<int, int>&, const pair<int, int>&)>> pq (
                [](const pair<int, int>& a, const pair<int, int>& b) {
                    return a.second > b.second;});
        pq.push ({start, 0});
        while (!pq.empty ()) {
            pair<int, int> cur = pq.top ();
            pq.pop ();
            int curID = cur.first;
            int curDistFromStart = cur.second;
            if (curDistFromStart > distTo [curID]) continue;
            // 到达当前节点有更好的路径，以此为基点加入符合条件的路径
            for (pair<int, int>& next : graph [curID]) {
                int nextID = next.first;
                int nextDistFromStart = distTo [curID] + next.second;
                if (nextDistFromStart < distTo [nextID]) {          // ***
                    distTo [nextID] = nextDistFromStart;            // ***
                    pq.push ({nextID, nextDistFromStart});
                }
            }
        }
        return distTo;
    }
};



// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution_L1_copy {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 节点编号是从 1 开始的，所以要一个大小为 n + 1 的邻接表
        vector<vector<pair<int, int>>> graph(n + 1);
        for (int i = 1; i <= n; i++) {
            graph[i] = vector<pair<int, int>>();
        }
        // 构造图
        for (auto& edge : times) {
            int from = edge[0];
            int to = edge[1];
            int weight = edge[2];
            // from -> List<(to, weight)>
            // 邻接表存储图结构，同时存储权重信息
            graph[from].emplace_back(to, weight);
        }
        // 启动 dijkstra 算法计算以节点 k 为起点到其他节点的最短路径
        vector<int> distTo = dijkstra(k, graph, n);

        // 找到最长的那一条最短路径
        int res = 0;
        for (int i = 1; i < distTo.size(); i++) {
            if (distTo[i] == INT_MAX) {
                // 有节点不可达，返回 -1
                return -1;
            }
            res = max(res, distTo[i]);
        }
        return res;
    }

private:
    // 输入一个起点 start，计算从 start 到其他节点的最短距离
    vector<int> dijkstra(int start, vector<vector<pair<int, int>>>& graph, int n) {
        // 定义：distTo[i] 的值就是起点 start 到达节点 i 的最短路径权重
        vector<int> distTo(n + 1, INT_MAX);
        // base case，start 到 start 的最短距离就是 0
        distTo[start] = 0;

        // 优先级队列，distFromStart 较小的排在前面
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        // 声明了一个优先队列（priority_queue），其中元素类型是 pair<int, int>，使用 vector<pair<int, int>> 作为底层容器，
        // 并且使用 greater<pair<int, int>> 作为比较函数，这意味着队列将按照 pair<int, int> 中的第一个元素进行升序排序，
        // 如果第一个元素相等，则按照第二个元素进行升序排序。

        // 从起点 start 开始进行 BFS
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto [curDistFromStart, curNodeID] = pq.top();
            pq.pop();

            if (curDistFromStart > distTo[curNodeID]) {
                continue;
            }
            // 有更好的路走：
            // 将 curNode 的相邻节点装入队列
            for (auto& [nextNodeID, weight] : graph[curNodeID]) {
                int distToNextNode = distTo[curNodeID] + weight;
                // 更新 dp table
                if (distTo[nextNodeID] > distToNextNode) {
                    distTo[nextNodeID] = distToNextNode;
                    pq.emplace(distToNextNode, nextNodeID);
                }
            }
        }
        return distTo;
    }
};
// 详细解析参见：
// https://labuladong.online/algo/slug.html?slug=network-delay-time
