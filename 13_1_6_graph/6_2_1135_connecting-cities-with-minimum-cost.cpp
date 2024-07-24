// 将所有边按照权重从小到大排序，从权重最小的边开始遍历，如果这条边和 mst 中的其它边不会形成环，
// 则这条边是最小生成树的一部分，将它加入 mst 集合；否则，这条边不是最小生成树的一部分，不要把它加入 mst 集合。
// https://leetcode.cn/problems/connecting-cities-with-minimum-cost


// 1135. 最低成本连通所有城市
// 中等
// 相关标签
// 相关企业
// 提示
// 想象一下你是个城市基建规划者，地图上有 n 座城市，它们按以 1 到 n 的次序编号。
// 给你整数 n 和一个数组 conections，其中 connections[i] = [xi, yi, costi] 表示将城市 xi 和城市 yi 连接所要的costi（连接是双向的）。
// 返回连接所有城市的最低成本，每对城市之间至少有一条路径。如果无法连接所有 n 个城市，返回 -1
// 该 最小成本 应该是所用全部连接成本的总和。

// 示例 1：
// 输入：n = 3, conections = [[1,2,5],[1,3,6],[2,3,1]]
// 输出：6
// 解释：选出任意 2 条边都可以连接所有城市，我们从中选取成本最小的 2 条。

// 示例 2：
// 输入：n = 4, conections = [[1,2,3],[3,4,4]]
// 输出：-1
// 解释：即使连通所有的边，也无法连接所有城市。

// 提示：
//     1 <= n <= 10^4
//     1 <= connections.length <= 10^4
//     connections[i].length == 3
//     1 <= xi, yi <= n
//     xi != yi
//     0 <= costi <= 105


#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using std::priority_queue;
using std::greater;
using std::vector;
using std::sort;
using std::pair;

class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
    
    }
};


// 14:59--15:16
// Kruskal 最小生成树 并查集uf + 贪心
class Solution_L1_M1 {
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        // 特殊情况
        if(n == 1) return 0;
        if(connections.size() < n-1) return -1;
        // cost排序
        sort(connections.begin(), connections.end(), [](const vector<int>& a, const vector<int>& b) {
            return a.back() < b.back(); // 按 cost 升序排列
        });
        // 开始构造最小生成树
        UF uf(n + 1);   // 从 1 开始
        int total = 0;
        for(auto& edge : connections) {
            int from = edge[0];
            int to = edge[1];
            int cost = edge[2];
            // 若这条边会产生环，则不能加入
            if(uf.connected(from, to)) continue;
            // 若这条边不会产生环，则属于最小生成树
            uf.union_(from, to);
            total += cost;
        }
        // 保证所有节点都被连通
        // 按理说 uf.count() == 1 说明所有节点被连通
        // 但因为节点 0 没有被使用，所以 0 会额外占用一个连通分量
        if(uf.count_() != 2) return -1; // 没连接所有节点, 0 是单独的
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



// 错误
#if 0
class Solution {
public:
    struct node{
        int to_index;
        int weight;
        node(int _to, int _w) : to_index(_to), weight(_w) {}
        // 构造小顶堆， 重载 >
        bool operator>(const node& other) const {
            return weight > other.weight;
        }
    };
    int minimumCost(int n, vector<vector<int>>& connections) {
        // 构造双向图
        vector<vector<node>> graph(n + 1);  // 从 1 开始
        for(auto edge : connections) {
            int from = edge[0];
            int to = edge[1];
            int cost = edge[2];
            graph[from].push_back(node(to, cost));
            graph[to].push_back(node(from, cost));
        }
        // 1 到其他节点的最短距离
        vector<int> costTo(n + 1,INT_MAX);
        costTo[1] = 0;
        // 小顶堆
        priority_queue<node,vector<node>,greater<node>> pq;
        pq.push(node(1, 0));
        int count = 1;  // 加入队列就标记
        // for(auto e : graph[1]) { // 将 1 连接的几个节点都加入队列
        //     pq.push(e);
        // }
        int cost = 0;
        while(!pq.empty()) {
            node cur = pq.top();
            pq.pop();
            int curID = cur.to_index;
            int curCost = cur.weight;
            // if(curID == n) return curCost;  // 不能提前结束
            if(curCost > costTo[curID]) continue;
            // 遇到花费更低的路径
            for(auto & next : graph[curID]) {
                int nextID = next.to_index;
                int nextCost = costTo[curID] + next.weight;
                if(nextCost < costTo[nextID]) {
                    costTo[nextID] = nextCost;
                    pq.push(node(nextID, nextCost));
                    count++;
                    cost += nextCost;   // 这是需要添加的新路
                }
            }
        }
        return count == n ? cost : -1;
    }
};
# endif


// Prim 最小生成树 切分 优先级队列
class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        // 将每条边转化为邻接表形式
        vector<vector<pair<int, int>>> graph(n);
        for(auto& connection : connections) {
            int from = connection[0] - 1;   // 编号从 1 开始
            int to = connection[1] - 1;
            int weight = connection[2];
            graph[from].push_back({to, weight});
            graph[to].push_back({from, weight});
        }
        // Prim 最小生成树算法
        Prim prim(graph);
        if(!prim.allConnected()) {
            return -1;
        }
        return prim.weightSum_();
    }
    // 只能判断能否生成最小生成树，以及权重和，不能判断有哪些边
    class Prim {
    private:
        struct Cmp {
            bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
                return a.second > b.second;
            }
        };
        // 小顶堆
        // 核心数据结构，存储 横切边的优先级队列
        // {from, to, weight} 表示一条边
        priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> pq;
        // visited 记录哪些节点已经成为最小生成树的一部分
        vector<bool> inMST;
        // 记录最小生成树的权重和
        int weightSum = 0;
        // graph[s]记录 s 所有相邻的边(连接到点和权重)
        vector<vector<pair<int, int>>>& graph;
    public:
        Prim(vector<vector<pair<int, int>>>& _graph) : graph(_graph) {
            int n = graph.size();   // 节点个数
            inMST.resize(n, false);
            // 随便从哪个节点分割都可以
            inMST[0] =  true;   // 节点从 0 开始
            cut(0);
            // 不断进行切分，向最小生成树添加边
            while(!pq.empty()) {
                // 每次找到权重最小的那个边
                pair<int, int> edge = pq.top();
                pq.pop();
                int to = edge.first;
                int weight = edge.second;
                if(inMST[to]) {
                    continue;   // 跳过已经在生成树中的节点
                }
                // 将边加入最小生成树
                weightSum += weight;
                // 边对应的新的节点加入最小生成树
                inMST[to] = true;
                // 节点加入后进行新一轮的切分
                cut(to);    // 在原来节点边的基础上加入新节点的边
            }
        }
        // 将 s 的横切便加入优先队列
        void cut(int s) {
            // 遍历 s 的邻边
            for(auto& edge : graph[s]) {
                int to = edge.first;
                if(inMST[to]) {
                    // 相邻的节点 to 已经在最小生成树中， 跳过
                    // 否则会产生环
                    continue;
                }
                // 加入横切边队列
                pq.push(edge);
            }
        }

        // 最小生成树的权重和
        int weightSum_() {
            return weightSum;
        }

        // 判断最小生成树是否包含图中的所有节点
        bool allConnected() {
            for(bool connected : inMST) {
                if(!connected) {
                    return false;
                }
            }
            return true;
        }
    };
};



// 10:08--10:40
// 如果需要给出生成树连接以及根节点
// connections[i] = [xi, yi, costi]
// i 从 1 开始
class Solution {
private:
    // 自定义数据结构，重载 >
    struct node {
        int from;   // 存储父节点           ***
        int to_index;
        int weight;
        node(int fro, int idx, int w) : from(fro), to_index(idx), weight(w) {}
        bool operator>(const node& other) const {
            return weight > other.weight;
        }
    };
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        // 将每条边转化为邻接表，双向
        vector<vector<node>> graph(n);
        for(auto& edge : connections) {
            int from = edge[0] - 1;
            int to = edge[1] - 1;
            int weight = edge[2];
            graph[from].push_back(node(from, to, weight));
            graph[to].push_back(node(to, from, weight));
        }
        Prim prim(n, graph);
        if(!prim.allConnected()) return -1;
        return prim.weightSum_();
    }
private:
    class Prim {
    private:
        vector<vector<node>>& m_graph;  // 双向邻接表
        vector<int> m_parent;   // 每个节点的父节点             ***
        vector<int> m_weight;   // 到达该节点所需边的 weight    ***
        vector<bool> m_visited; // 是否遍历过
        // 最重要的数据结构，弹出切割边中最小的那个
        priority_queue<node, vector<node>, greater<node>> pq;
        int weightSum;
    public:
        Prim(int n, vector<vector<node>>& graph) : m_graph(graph) {
            m_parent.resize(n, -1);         // 所有父节点 -1
            m_weight.resize(n, INT_MAX);
            m_visited.resize(n, false);
            weightSum = 0;
            // 从 0 开始 切割，这里可以根据参数选择
            m_visited[0] = true;
            cut(0);
            // 不断进行切人，向最小生成树添加边
            while(!pq.empty()) {
                auto cur = pq.top();    // 最小边
                pq.pop();
                int from = cur.from;
                int to = cur.to_index;
                int weight = cur.weight;
                if(m_visited[to]) {
                    continue;
                }
                weightSum += weight;
                m_parent[to] = from;
                m_weight[to] = weight;
                m_visited[to] = true;
                cut(to);
            }

        }
        void cut(int cur) {
            for(auto edge : m_graph[cur]) {
                int next = edge.to_index;
                if(m_visited[next]) {
                    continue;
                }
                pq.push(edge);
            }
        }
        bool allConnected() {
            for(auto temp : m_visited) {
                if(!temp) return false;
            }
            return true;
        }
        int weightSum_() {
            return weightSum;
        }
    };
};

