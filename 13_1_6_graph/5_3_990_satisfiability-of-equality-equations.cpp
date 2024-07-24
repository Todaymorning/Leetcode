// 990. 等式方程的可满足性
// https://leetcode.cn/problems/satisfiability-of-equality-equations/
// 中等
// 给定一个由表示变量之间关系的字符串方程组成的数组，每个字符串方程 equations[i] 的长度为 4，
// 并采用两种不同的形式之一："a==b" 或 "a!=b"。在这里，a 和 b 是小写字母（不一定不同），表示单字母变量名。
// 只有当可以将整数分配给变量名，以便满足所有给定的方程时才返回 true，否则返回 false。 

// 示例 1：
// 输入：["a==b","b!=a"]
// 输出：false
// 解释：如果我们指定，a = 1 且 b = 1，那么可以满足第一个方程，但无法满足第二个方程。没有办法分配变量同时满足这两个方程。

// 示例 2：
// 输入：["b==a","a==b"]
// 输出：true
// 解释：我们可以指定 a = 1 且 b = 1 以满足满足这两个方程。

// 示例 3：
// 输入：["a==b","b==c","a==c"]
// 输出：true

// 示例 4：
// 输入：["a==b","b!=c","c==a"]
// 输出：false

// 示例 5：
// 输入：["c==c","b==d","x!=z"]
// 输出：true

// 提示：
// 1 <= equations.length <= 500
// equations[i].length == 4
// equations[i][0] 和 equations[i][3] 是小写字母
// equations[i][1] 要么是 '='，要么是 '!'
// equations[i][2] 是 '='


#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {

    }
};


// 20:37--20:41(读题找思路)--20:59
// 两个并查集，一个找相等，一个找不等，在连接前判断另一个是否相连
// 字母到数字的映射 a-z --> 0-25
#if 0
class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        UF equal(26);
        UF not_equal(26);
        for(auto e:equations) {
            int p = e[0] - 'a';
            int q = e[3] - 'a';
            // 两个字母相等
            if(p == q) {
                if(e[1] == '!') return false;   // 自己不相等
                else continue;                  // 自己想等
            }
            // 两个字母不相等
            if(e[1] == '=') {
                if(not_equal.isConnected(p, q)) return false;
                equal.union_(p, q);
            }
            else {
                if(equal.isConnected(p, q)) return false;
                not_equal.union_(p, q);
            }
        }
        return true;
    }

    class UF {
    private:
        vector<int> parent;
    public:
        UF(int n) {
            parent = vector<int>(n);
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
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                parent[rootX] = rootY;
            }
        }
        bool isConnected(int x, int y) {
            return find(x) == find(y);
        }
    };
};
#endif


// 核心思想是，将 equations 中的算式根据 == 和 != 分成两部分，先处理 == 算式，
// 使得他们通过相等关系各自勾结成门派（连通分量）；然后处理 != 算式，检查不等关系是否破坏了相等关系的连通性。
class Solution_L1_M2 {
public:
    bool equationsPossible(vector<string>& equations) {
        UF uf(26);
        // 先处理相等关系
        for(auto e:equations) {
            if(e[1] == '=') {
                uf.union_(e[0] - 'a', e[3] - 'a');
            }
        }
        // 再查询不等关系是否破坏了连通性
        for(auto e:equations) {
            if(e[1] == '!') {
                if(uf.isConnected(e[0] - 'a', e[3] - 'a')) {
                    return false;
                }
            }
        }
        return true;
    }

    class UF {
    private:
        vector<int> parent;
    public:
        UF(int n) {
            parent = vector<int>(n);
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
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                parent[rootX] = rootY;
            }
        }
        bool isConnected(int x, int y) {
            return find(x) == find(y);
        }
    };
};