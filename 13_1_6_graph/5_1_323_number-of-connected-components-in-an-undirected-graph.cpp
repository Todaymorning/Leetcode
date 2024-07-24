// https://leetcode.cn/problems/number-of-connected-components-in-an-undirected-graph/
// 323. 无向图中连通分量的数目
// 中等
// 你有一个包含 n 个节点的图。给定一个整数 n 和一个数组 edges ，其中 edges[i] = [ai, bi] 表示图中 ai 和 bi 之间有一条边。
// 返回 图中已连接分量的数目 。

// 示例 1:
// 输入: n = 5, edges = [[0, 1], [1, 2], [3, 4]]
// 输出: 2

// 示例 2:
// 输入: n = 5, edges = [[0,1], [1,2], [2,3], [3,4]]
// 输出:  1

// 提示：
//     1 <= n <= 2000
//     1 <= edges.length <= 5000
//     edges[i].length == 2
//     0 <= ai <= bi < n
//     ai != bi
//     edges 中不会出现重复的边

#include<iostream>
#include<vector>
using std::vector;


class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {

    }
};



class UF1 {
private:
    int count;      // 联通分量个数
    int *parent;    // 每个节点的父节点
public:
    // n 图中节点的个数
    UF1(int n) {
        count = n;
        parent = new int[n];
        for(int i=0; i<n; i++) {
            parent[i] = i;  // 每个节点先指向自己，即每个节点的父节点都是自己
        }
    }
    // 找到指点节点 x 的根节点
    int find(int x) {
        // 如果 x 不是根节点，if语句均会执行，把树压平
        // 但当树本身就是平的时，这里还是会执行，稍微有点多余，但不影响
        if(parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    // 联通两个节点
    void union_(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if(rootP == rootQ) return;
        parent[rootQ] = rootP;  // 这里将两个根节点连接，此时树可能不是平的，不影响复杂度，每次调用find都会将其压平
        count--;
    }
    // 判断两个节点是否联通
    bool connected(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        return rootP == rootQ;
    }
    // 返回图中联通分量的个数
    int count_() {
        return count;
    }

};



class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        UF uf(n);
        for(int i=0; i<edges.size(); i++) {
            uf.union_(edges[i][0], edges[i][1]);
        }
        return uf.count_();
    }
    class UF {
    private:
        int count;      // 联通分量个数
        int *parent;    // 每个节点的父节点
    public:
        // n 图中节点的个数
        UF(int n) {
            count = n;
            parent = new int[n];
            for(int i=0; i<n; i++) {
                parent[i] = i;  // 每个节点先指向自己，即每个节点的父节点都是自己
            }
        }
        // 找到指点节点 x 的根节点
        int find(int x) {
            // 如果 x 不是根节点，if语句均会执行，把树压平
            // 但当树本身就是平的时，这里还是会执行，稍微有点多余，但不影响
            if(parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        // 联通两个节点
        void union_(int p, int q) {
            int rootP = find(p);
            int rootQ = find(q);
            if(rootP == rootQ) return;
            parent[rootQ] = rootP;  // 这里将两个根节点连接，此时树可能不是平的，不影响复杂度，每次调用find都会将其压平
            count--;
        }
        // 判断两个节点是否联通
        bool connected(int p, int q) {
            int rootP = find(p);
            int rootQ = find(q);
            return rootP == rootQ;
        }
        // 返回图中联通分量的个数
        int count_() {
            return count;
        }

    };
};