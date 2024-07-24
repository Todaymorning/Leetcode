// 63. 不同路径 II
// 思路
// 中等
// 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
// 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。
// 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
// 网格中的障碍物和空位置分别用 1 和 0 来表示。

// 示例 1：
// 输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
// 输出：2
// 解释：3x3 网格的正中间有一个障碍物。
// 从左上角到右下角一共有 2 条不同的路径：
// 1. 向右 -> 向右 -> 向下 -> 向下
// 2. 向下 -> 向下 -> 向右 -> 向右

// 示例 2：
// 输入：obstacleGrid = [[0,1],[0,0]]
// 输出：1

// 提示：
// m == obstacleGrid.length
// n == obstacleGrid[i].length
// 1 <= m, n <= 100
// obstacleGrid[i][j] 为 0 或 1


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

    }
};

// 14:41--14:46(读题找思路)--14:59(错误)--15:14
// 上、左有一个有阻碍时，只加另一个方向
// 上左都有阻碍时，该单元格也变成阻碍
// dp [i][j] ：表示从（0 ，0）出发，到 (i, j) 有 dp [i][j] 条不同的路径。
// dp [i][j] = dp [i - 1][j] + dp [i][j - 1]
class Solution_M1 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 1));
        // 初始化 0 列                      ***
        for(int i=0; i<m; i++) {
            if(obstacleGrid[i][0] == 1) {
                while(i<m) dp[i++][0] = 0;  // 下面全不通
            }
        }
        // 初始化 0 行                      ***
        for(int i=0; i<n; i++) {
            if(obstacleGrid[0][i] == 1) {
                while(i<n) dp[0][i++] = 0;  // 右边全不通
            }
        }
        // 从 1 行 1 列开始
        for(int i = 1; i<m; i++) {
            for(int j=1; j<n; j++) {
                // 当前单元格有阻碍
                if(obstacleGrid[i][j] == 1) dp[i][j] = 0;
                // 上、左单元格都有阻碍
                else if(obstacleGrid[i-1][j] == 1 && obstacleGrid[i][j-1] == 1) dp[i][j] = 0;
                else if(dp[i-1][j] == 0 && dp[i][j-1] == 0) dp[i][j] = 0;
                // 上、左单元格至少有一个通
                else dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};



// 15:14--15:19(看 D1思路和代码)--15:33
// 时间复杂度：O (n × m)，n、m 分别为 obstacleGrid 长度和宽度
// 空间复杂度：O (n × m)
class Solution_D1_M2 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        // 起点或终点出现障碍
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) return 0;
        // 初始化
        vector<vector<int>> dp(m, vector<int>(n, 0));   // 初始化为 0
        // 第 0 列从上到下初始化为 1，直到遇到阻碍（下面都是 0）
        for(int i=0; i<m && obstacleGrid[i][0] == 0; i++) dp[i][0] = 1;
        // 第 0 列从左到右初始化为 1，直到遇到阻碍（右边都是 0）
        for(int i=0; i<n && obstacleGrid[0][i] == 0; i++) dp[0][i] = 1;
        // 从第 1 行第 1 列递推
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                if(obstacleGrid[i][j] == 1) dp[i][j] = 0;   // 当前单元格有阻碍
                else dp[i][j] = dp[i-1][j] + dp[i][j-1];
                // // 与下面等价
                // if(obstacleGrid[i][j] == 1) continue;
                // dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};


// 15:34--15:51(错误，索引的 i j)--15:57
// 空间优化，使用两个向量
class Solution_M3 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) return 0;
        vector<int> dpCol(n, 0);
        vector<int> dpRow(m, 0);
        // vector<int> dpCol(m, 0);
        for(int i=0; i<n && obstacleGrid[0][i] == 0; i++) dpCol[i] = 1;
        for(int i=0; i<m && obstacleGrid[i][0] == 0; i++) dpRow[i] = 1;
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                if(obstacleGrid[i][j] == 1) {
                    dpCol[j] = 0;
                    dpRow[i] = 0;   // ***
                }
                else {
                    dpCol[j] += dpRow[i];
                    dpRow[i] = dpCol[j];
                }
            }
        }
        return dpCol.back();
    }
};



// 16:02--16:30(看L3+写，少了初始化)--16:34
// 空间优化：只用一个向量
class Solution_L3_M4 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1] == 1) return 0;
        vector<int> dp(n, 0);
        // 初始化
        dp[0] = obstacleGrid[0][0] == 1 ? 0 : 1;    // ***
        // 从第 0 行 第 0 列开始递推
        for(int i = 0; i<m; i++) { 
            for(int j = 0; j<n; j++) {
                if(obstacleGrid[i][j] == 1) {   // 第 0 行时，没遇到阻碍时都是 1，遇到后后面就都是 0 了
                    dp[j] = 0;
                }
                else if(j>0) {  // 第 1 列开始
                    dp[j] += dp[j-1];
                }
            }
        }
        return dp.back();
    }
};




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码不保证正确性，仅供参考。如有疑惑，可以参照我写的 java 代码对比查看。

// 第一步：自顶向下带备忘录的递归
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        memo = vector<vector<int>>(m, vector<int>(n, 0));
        return dp(obstacleGrid, m - 1, n - 1);
    }

    // 备忘录
    vector<vector<int>> memo;

    // 定义：从 grid[0][0] 出发到达 grid[i][j] 的路径条数为 dp(grid, i, j)
    int dp(vector<vector<int>>& grid, int i, int j) {
        int m = grid.size(), n = grid[0].size();
        // base case
        if (i < 0 || i >= m || j < 0 || j >= n
                || grid[i][j] == 1) {
            // 数组越界或者遇到阻碍
            return 0;
        }
        if (i == 0 && j == 0) {
            // 起点到起点的路径条数就是 1
            return 1;
        }
        if (memo[i][j] > 0) {
            // 避免冗余计算
            return memo[i][j];
        }
        // 状态转移方程：
        // 到达 grid[i][j] 的路径条数等于
        // 到达 grid[i-1][j] 的路径条数加上到达 grid[i][j-1] 的路径条数
        int left = dp(grid, i, j - 1);
        int upper = dp(grid, i - 1, j);
        int res = left + upper;
        // 存储备忘录
        memo[i][j] = res;
        return res;
    }
};

// 第二步：自底向上迭代的动态规划
class Solution2 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        // 数组索引偏移一位，dp[0][..] dp[..][0] 代表 obstacleGrid 之外
        // 定义：到达 obstacleGrid[i][j] 的路径条数为 dp[i-1][j-1]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // base case：如果没有障碍物，起点到起点的路径条数就是 1
        dp[1][1] = obstacleGrid[0][0] == 1 ? 0 : 1;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == 1 && j == 1) {
                    // 跳过 base case
                    continue;
                }
                if (obstacleGrid[i - 1][j - 1] == 1) {
                    // 跳过障碍物的格子
                    continue;
                }
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        // 返回到达 obstacleGrid[m-1][n-1] 的路径数量
        return dp[m][n];
    }
};

// 第三步：优化二维 dp 数组为一维 dp 数组
class Solution3 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        // 根据二维 dp 数组优化为一维 dp 数组
        vector<int> dp(n + 1, 0);
        dp[1] = obstacleGrid[0][0] == 1 ? 0 : 1;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == 1 && j == 1) {
                    // 跳过 base case
                    continue;
                }
                if (obstacleGrid[i - 1][j - 1] == 1) {
                    // 跳过障碍物的格子
                    dp[j] = 0;
                    continue;
                }
                dp[j] = dp[j] + dp[j - 1];
            }
        }
        // 返回到达 obstacleGrid[m-1][n-1] 的路径数量
        return dp[n];
    }
};