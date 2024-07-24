// 56. 携带矿石资源（第八期模拟笔试）
// 时间限制：5.000S  空间限制：256MB
// 题目描述
// 你是一名宇航员，即将前往一个遥远的行星。在这个行星上，有许多不同类型的矿石资源，每种矿石都有不同的重要性和价值。你需要选择哪些矿石带回地球，但你的宇航舱有一定的容量限制。 
// 给定一个宇航舱，最大容量为 C。现在有 N 种不同类型的矿石，每种矿石有一个重量 w [i]，一个价值 v [i]，以及最多 k [i] 个可用。
// 不同类型的矿石在地球上的市场价值不同。你需要计算如何在不超过宇航舱容量的情况下，最大化你所能获取的总价值。

// 输入描述
// 输入共包括四行，第一行包含两个整数 C 和 N，分别表示宇航舱的容量和矿石的种类数量。 
// 接下来的三行，每行包含 N 个正整数。具体如下： 
// 第二行包含 N 个整数，表示 N 种矿石的重量。 
// 第三行包含 N 个整数，表示 N 种矿石的价格。 
// 第四行包含 N 个整数，表示 N 种矿石的可用数量上限。

// 输出描述
// 输出一个整数，代表获取的最大价值。

// 输入示例
// 10 3
// 1 3 4
// 15 20 30
// 2 3 2
// 输出示例
// 90
// 提示信息
// 数据范围：
// 1 <= C <= 10000;
// 1 <= N <= 10000;
// 1 <= w[i], v[i], k[i] <= 10000;


// 16:52--16:58(框架)--17:07--17:10(未知错误，使用vs调试)--17:25(应该初始化为0 而不是 INT_MIN)--17:26(超时)
// 多重背包转换为 01 背包
// 
#include<iostream>
#include<vector>
using std::vector;

// 转化为 01 背包
class Solution {
public:
    int solve(int bag, vector<int>& weight, vector<int>& value, vector<int>& num) {
        // 多重背包转化为 01 背包
        int sum = 0;
        for(int n:num) sum+=n;   // 统计物品个数
        vector<int> new_weight(sum, 0);
        vector<int> new_value(sum, 0);
        int idx = 0;
        for(int i=0; i<num.size(); i++) {
            int temp = num[i];
            while(temp > 0) {
                new_weight[idx] = weight[i];    // 多重转为 01
                new_value[idx] = value[i];
                idx++;
                temp--;
            }
        }
        // 求解 01 背包
        vector<int> dp(bag+1, 0);   // ***
        for(int i=0; i<new_weight.size(); i++) {    // 遍历物品
            for(int j=bag; j>=new_weight[i]; j--) { // 遍历背包，倒序
                dp[j] = std::max(dp[j], dp[j-new_weight[i]] + new_value[i]);
            }
        }
        return dp.back();
    }
};

// 17:27--17:33
class Solution_D2 {
public:
    int solve(int bag, vector<int>& weight, vector<int>& value, vector<int>& num) {
        vector<int> dp(bag+1, 0);
        for(int i=0; i<num.size(); i++) {   // 遍历物品
            for(int j=0; j<num[i]; j++) {   // 遍历个数，可以重复利用的个数
                for(int k=bag; k>=weight[i]; k--) { // 遍历背包
                    dp[k] = std::max(dp[k], dp[k - weight[i]] + value[i]);
                }
            }
        }
        return dp.back();
    }
};


int main() {
    int C;
    int N;
    std::cin >> C >> N;
    vector<int> weight(N, 0);
    vector<int> value(N, 0);
    vector<int> num(N, 0);
    for(int i=0; i<N; i++) std::cin >> weight[i];
    for(int i=0; i<N; i++) std::cin >> value[i];
    for(int i=0; i<N; i++) std::cin >> num[i];
    Solution ss;
    std::cout << ss.solve(C, weight, value, num);
    return 0;
}
