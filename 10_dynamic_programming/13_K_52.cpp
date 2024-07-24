// 52. 携带研究材料（第七期模拟笔试）
// 时间限制：1.000S  空间限制：128MB
// 题目描述
// 小明是一位科学家，他需要参加一场重要的国际科学大会，以展示自己的最新研究成果。他需要带一些研究材料，但是他的行李箱空间有限。
// 这些研究材料包括实验设备、文献资料和实验样本等等，它们各自占据不同的空间，并且具有不同的价值。
// 小明的行李空间为 N，问小明应该如何抉择，才能携带最大价值的研究材料，每种研究材料可以选择无数次，并且可以重复选择。

// 输入描述
// 第一行包含两个整数，N，V，分别表示研究材料的种类和行李空间 
// 接下来包含 N 行，每行两个整数 wi 和 vi，代表第 i 种研究材料的重量和价值

// 输出描述
// 输出一个整数，表示最大价值。

// 输入示例
// 4 5
// 1 2
// 2 4
// 3 4
// 4 5
// 输出示例
// 10
// 提示信息
// 第一种材料选择五次，可以达到最大值。

// 数据范围：
// 1 <= N <= 10000;
// 1 <= V <= 10000;
// 1 <= wi, vi <= 10^9.

// 16:07--16:18
#include<iostream>
#include<vector>
using std::vector;


// 完全背包
// 01 背包中二维 dp 数组的两个 for 遍历的先后循序是可以颠倒了
// 01 背包中一维 dp 数组的两个 for 循环先后循序一定是先遍历物品，再遍历背包容量。
// 完全背包中，对于一维 dp 数组来说，其实两个 for 循环嵌套顺序是无所谓的！
// 因为 dp [j] 是根据 下标 j 之前所对应的 dp [j] 计算出来的。 只要保证下标 j 之前的 dp [j] 都是经过计算的就可以了。

// 先遍历物品再遍历背包
class Solution_D1 {
public:
    int solve(int N, int V, vector<int>& wi, vector<int>& vi) {
        vector<int> dp(V+1, 0);
        for(int i=0; i<N; i++) {        // 遍历物品
            for(int j=wi[i]; j<=V; j++) {   // 遍历空间，从前往后遍历
                dp[j] = std::max(dp[j], dp[j - wi[i]] + vi[i]);
            }
        }
        return dp.back();
    }
};

// 先遍历背包再遍历物品
class Solution_D2 {
public:
    int solve(int N, int V, vector<int>& wi, vector<int>& vi) {
        vector<int> dp(V+1, 0);
        for(int j=0; j<=V; j++) {
            for(int i=0; i<N; i++) {
                if(j >= wi[i]) dp[j] = std::max(dp[j], dp[j-wi[i]] + vi[i]);
            }
        }
        return dp.back();
    }
};

int main() {
    int N, V;
    std::cin >> N >> V;
    vector<int> wi(N, 0);
    vector<int> vi(N, 0);
    for(int i=0; i<N; i++) {
        std::cin >> wi[i] >> vi[i];
    }
    Solution_D2 ss;
    std::cout << ss.solve(N, V, wi, vi);
    return 0;
}