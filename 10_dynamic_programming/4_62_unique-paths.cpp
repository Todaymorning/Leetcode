// 62. 不同路径
// 思路
// 中等
// 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
// 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
// 问总共有多少条不同的路径？

// 示例 1：
// 输入：m = 3, n = 7
// 输出：28

// 示例 2：
// 输入：m = 3, n = 2
// 输出：3
// 解释：
// 从左上角开始，总共有 3 条路径可以到达右下角。
// 1. 向右 -> 向下 -> 向下
// 2. 向下 -> 向下 -> 向右
// 3. 向下 -> 向右 -> 向下

// 示例 3：
// 输入：m = 7, n = 3
// 输出：28

// 示例 4：
// 输入：m = 3, n = 3
// 输出：6

// 提示：
// 1 <= m, n <= 100
// 题目数据保证答案小于等于 2 * 10^9



#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int uniquePaths(int m, int n) {

    }
};

// 11:40--11:51(i,j错误)--12:01
// 时间复杂度：O (m × n)
// 空间复杂度：O (m × n)
class Solution_M1_D1 {
public:
    int uniquePaths(int m, int n) {
        // dp[m][n]，到该点有多少种走法
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {    // *** j<n,写成了i<n
                dp[i][j] = dp[i-1][j] + dp[i][j-1]; // 上面和左边走法的和
            }
        }
        return dp[m-1][n-1];
    }
};


// 12:01-12:10(错误)--12:20
// 时间复杂度：O (m × n)
// 空间复杂度：O (n)
class Solution_M2 {
public:
    int uniquePaths(int m, int n) {
        // vector<int> dpCol(m, 1);    // 列向量
        vector<int> dpRow(n, 1);    // 行向量
        int dpCol = 1;              // 列元素
        for(int i=1; i<m; i++) {
            dpCol = 1;  // 从1开始
            for(int j=1; j<n; j++) {
                // dpCol[i] = dpCol[i-1] + dpRow[j-1];
                // dpRow[j] = dpCol[i];
                dpRow[j] = dpRow[j] + dpCol;    // 更新每一行的元素时，只需要用到列中的一个元素，及时更新即可
                dpCol = dpRow[j];   // 更新列元素
            }
        }
        return dpRow.back();
    }
};


// 按行更新
class Solution_M2_2 {
public:
    int uniquePaths(int m, int n) {
        vector<int> dpRow(n, 1);    // 行向量
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                dpRow[j] += dpRow[j-1];    // 更新每一行的元素时，只需要用到列中的一个元素，及时更新即可
            }
        }
        return dpRow.back();
    }
};

// 按列更新
class Solution_D2_copy {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);  // 行向量
        for (int j = 1; j < m; j++) {
            for (int i = 1; i < n; i++) {
                dp[i] += dp[i - 1];
            }
        }
        return dp[n - 1];
    }
};


// 深搜
// 这道题目，刚一看最直观的想法就是用图论里的深搜，来枚举出来有多少种路径。
// 注意题目中说机器人每次只能向下或者向右移动一步，那么其实机器人走过的路径可以抽象为一棵二叉树，而叶子节点就是终点！
// 时间超标
// 来分析一下时间复杂度，这个深搜的算法，其实就是要遍历整个二叉树。
// 这棵树的深度其实就是 m+n-1（深度按从 1 开始计算）。
// 那二叉树的节点个数就是 2^(m + n - 1) - 1。可以理解深搜的算法就是遍历了整个满二叉树（其实没有遍历整个满二叉树，只是近似而已）
// 所以上面深搜代码的时间复杂度为 O (2^(m + n - 1) - 1)，可以看出，这是指数级别的时间复杂度，是非常大的。
class Solution_D1_copy {
    int dfs(int m, int n, int startm, int startn) {
        if(startm > m || startn > n) return 0;
        if(startm == m && startn == n) return 1;    // 找到一种路径
        return dfs(m, n, startm+1, startn) + dfs(m, n, startm, startn+1);   // 向下走一步后路径的个数 + 向右走一步路径的个数
    }
public:
    int uniquePaths(int m, int n) {
        return dfs(m, n, 1, 1);
    }
};