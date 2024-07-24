// 474. 一和零
// 中等
// 给你一个二进制字符串数组 strs 和两个整数 m 和 n 。
// 请你找出并返回 strs 的最大子集的长度，该子集中 最多 有 m 个 0 和 n 个 1 。
// 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。

// 示例 1：
// 输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
// 输出：4
// 解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是 4 。
// 其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"} 。{"111001"} 不满足题意，因为它含 4 个 1 ，大于 n 的值 3 。

// 示例 2：
// 输入：strs = ["10", "0", "1"], m = 1, n = 1
// 输出：2
// 解释：最大的子集是 {"0", "1"} ，所以答案是 2 。

// 提示：
// 1 <= strs.length <= 600
// 1 <= strs[i].length <= 100
// strs[i] 仅由 '0' 和 '1' 组成
// 1 <= m, n <= 100


#include<iostream>
#include<vector>
#include<string>
using std::vector;
using std::string;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {

    }
};


// 14:35--14:59(读题，尝试未成功)--15:30(看 D1 思路)--15:37
// vector<string> 转化为vector<vector<int>>
// dp [i][j]：最多有 i 个 0 和 j 个 1 的 strs 的最大子集的大小为 dp [i][j]。
// 然后我们在遍历的过程中，取 dp [i][j] 的最大值。
// 所以递推公式：dp [i][j] = max (dp [i][j], dp [i - zeroNum][j - oneNum] + 1);
// 此时大家可以回想一下 01 背包的递推公式：dp [j] = max (dp [j], dp [j - weight [i]] + value [i]);
// 对比一下就会发现，字符串的 zeroNum 和 oneNum 相当于物品的重量（weight [i]），字符串本身的个数相当于物品的价值（value [i]）。
// 这就是一个典型的 01 背包！ 只不过物品的重量有了两个维度而已。

// 时间复杂度: O (kmn)，k 为 strs 的长度
// 空间复杂度: O (mn)

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));   // ***
        for(string s:strs) {    // 遍历物品
            int zeros = 0;
            int ones = 0;
            for(char ch:s) {
                if(ch == '0') zeros++;
                else ones++;
            }
            // 下面的两个遍历能够反过来，从后往前遍历
            for(int i=m; i>=zeros; i--) {       // 遍历 行      // ***
                for(int j=n; j>=ones; j--) {    // 遍历列
                    dp[i][j] = std::max(dp[i][j], dp[i - zeros][j - ones] + 1);
                }
            }
        }
        return dp[m][n];
    }
};