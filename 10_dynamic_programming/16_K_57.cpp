// 57. 爬楼梯（第八期模拟笔试）
// 时间限制：1.000S  空间限制：128MB
// 题目描述
// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。 
// 每次你可以爬至多 m (1 <= m < n) 个台阶。你有多少种不同的方法可以爬到楼顶呢？ 
// 注意：给定 n 是一个正整数。

// 输入描述
// 输入共一行，包含两个正整数，分别表示 n, m
// 输出描述
// 输出一个整数，表示爬到楼顶的方法数。

// 输入示例
// 3 2
// 输出示例
// 3
// 提示信息
// 数据范围：
// 1 <= m < n <= 32;
// 当 m = 2，n = 3 时，n = 3 这表示一共有三个台阶，m = 2 代表你每次可以爬一个台阶或者两个台阶。
// 此时你有三种方法可以爬到楼顶。
// 1. 1 阶 + 1 阶 + 1 阶段
// 2. 1 阶 + 2 阶
// 3. 2 阶 + 1 阶

// 11:40--11：43(读题找思路，完全背包排列组合)
// n个台阶，每次爬 [1, m] 个
// nums = {1, 2, ..., m}，求和为 n 的排列组合个数
// 完全背包排列组合

#include<iostream>
#include<vector>
using std::vector;

// 11:45--11:50
// 时间复杂度: O (n * m)
// 空间复杂度: O (n)
class Solution_M1 {
public:
    int solve(int n, int m) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        for(int j=1; j<=n; j++) { // 遍历背包 n
            for(int i=1; i<=m; i++) {   // 遍历物品 1, 2, 3, ... m
                if(j >= i) {
                    dp[j] = dp[j] + dp[j - i];  // **  j - i
                }
            }
        }
        return dp.back();
    }
};

// 11:50--11:55,12:01(越界)
// 潜在的数组或指针越界，请检查代码。
class Solution_M2 {
public:
    int solve(int n, int m) {
        // 有物品+1个行，背包+1个列
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=0; i<=m; i++) {
            dp[i][0] = 1;
        }
        for(int j=1; j<=n; j++) {       // 遍历背包
            for(int i=1; i<=m; i++) {   // 遍历物品
                if(j >= i) {
                    dp[i][j] = dp[i-1][j] + dp[m][j - i];
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[m][n];    // 忘了返回         ***
    }
};


int main() {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    Solution_M1 ss;
    std::cout << ss.solve(n, m);
    return 0;
}


