// 46. 携带研究材料（第六期模拟笔试）
// 时间限制：5.000S  空间限制：128MB
// 题目描述
// 小明是一位科学家，他需要参加一场重要的国际科学大会，以展示自己的最新研究成果。他需要带一些研究材料，但是他的行李箱空间有限。
// 这些研究材料包括实验设备、文献资料和实验样本等等，它们各自占据不同的空间，并且具有不同的价值。 
// 小明的行李空间为 N，问小明应该如何抉择，才能携带最大价值的研究材料，每种研究材料只能选择一次，并且只有选与不选两种选择，不能进行切割。

// 输入描述
// 第一行包含两个正整数，第一个整数 M 代表研究材料的种类，第二个正整数 N，代表小明的行李空间。
// 第二行包含 M 个正整数，代表每种研究材料的所占空间。 
// 第三行包含 M 个正整数，代表每种研究材料的价值。

// 输出描述
// 输出一个整数，代表小明能够携带的研究材料的最大价值。
// 输入示例
// 6 1
// 2 2 3 1 5 2
// 2 3 1 5 4 3
// 输出示例
// 5
// 提示信息
// 小明能够携带 6 种研究材料，但是行李空间只有 1，而占用空间为 1 的研究材料价值为 5，所以最终答案输出 5。 

// 数据范围：
// 1 <= N <= 1000
// 1 <= M <= 1000
// 研究材料占用空间和价值都小于等于 1000


// 就是本文中的题目，要求先实现一个纯二维的 01 背包，如果写出来了，然后再问为什么两个 for 循环的嵌套顺序这么写？反过来写行不行？再讲一讲初始化的逻辑。
// 然后要求实现一个一维数组的 01 背包，最后再问，一维数组的 01 背包，两个 for 循环的顺序反过来写行不行？为什么？
// 注意以上问题都是在候选人把代码写出来的情况下才问的。
// 就是纯 01 背包的题目，都不用考 01 背包应用类的题目就可以看出候选人对算法的理解程度了。


// 9:54--10:10(框架)
#include<iostream>
#include<vector>
#include<algorithm>
using std::sort;
using std::vector;
using std::cin;
class Solution {
public:
    void solve(int bag, vector<int>& weights, vector<int>& value) {
        
    }
};

// 10:10--10:28(错误，没有考虑到性价比的问题)
// 贪心：每次尽量放重量小价值大的物品
// 价值相同按重量升序
// 价值不同按价值降序
#if 0
class Solution {
public:
    int solve(int bag, vector<int>& weights, vector<int>& value) {
        vector<vector<int>> obj(weights.size(), vector<int>(2, 0));
        for(int i=0; i<weights.size(); i++) {
            obj[i][0] = weights[i];
            obj[i][1] = value[i];
        }
        sort(obj.begin(), obj.end(), [](const vector<int>& a, const vector<int>& b) {
            if(a[1] == b[1]) return a[0] < b[0];    // 价值相同按重量升序
            return a[1] > b[1];                     // 价值不同按价值降序
        });
        int result = 0;
        for(int i=0; i<obj.size(); i++) {
            bag -= obj[i][0];
            if(bag >= 0) result += obj[i][1];    // 可以放下
        }
        return result;
    }
};
#endif

// 10:52--10:56(动态规划不会，只想到了一个回溯的方法)--11:05(超时)
// 回溯
#if 0
class Solution {
private:
    int result = 0;
    int track = 0;
    vector<bool> used;
    void backtracking(int bag, vector<int>& weights, vector<int>& value) {
        if(bag <= 0) return;
        for(int i=0; i<weights.size(); i++) {
            if(used[i] == true || bag-weights[i] < 0) continue;
            used[i] = true;
            track += value[i];
            if(track > result) result = track;
            backtracking(bag-weights[i], weights, value);
            used[i] = false;
            track -= value[i];
        }
    }
public:
    int solve(int bag, vector<int>& weights, vector<int>& value) {
        result = 0;
        used = vector<bool>(weights.size(), false);
        backtracking(bag, weights, value);
        return result;
    }
};
#endif

// 11:05--11:18(修改回溯：排序后剪枝优化(超时))
#if 0
class Solution {
private:
    int result = 0;
    int track = 0;
    vector<bool> used;
    void backtracking(int bag, vector<vector<int>>& obj) {
        if(bag <= 0) return;
        for(int i=0; i<obj.size(); i++) {
            if(used[i] == true) continue;
            if(bag - obj[i][0] < 0) return; // 直接 return，后面不用递归了
            used[i] = true;
            track += obj[i][1];
            if(track > result) result = track;
            backtracking(bag-obj[i][0], obj);
            used[i] = false;
            track -= obj[i][1];
        }
    }
public:
    int solve(int bag, vector<int>& weights, vector<int>& value) {
        result = 0;
        used = vector<bool>(weights.size(), false);
        vector<vector<int>> obj(weights.size(), vector<int>(2, 0));
        for(int i=0; i<weights.size(); i++) {
            obj[i][0] = weights[i];
            obj[i][1] = value[i];
        }
        std::sort(obj.begin(), obj.end(), [](auto a, auto b) {
            if(a[0] == b[0]) return a[1] > b[1];    // 重量相同时，价值从大往小排
            return a[0] < b[0];                     // 重量从小到大排
        });
        backtracking(bag, obj);
        return result;
    }
};
#endif

// 15:42--16:21
// 背包问题，动态规划，二维数组
class Solution_D1 {
public:
    int solve(int bag, vector<int>& weights, vector<int>& values) {
        // dp数组, dp[i][j]代表行李箱空间为j的情况下,从下标为[0, i]的物品里面任意取,能达到的最大价值
        vector<vector<int>> dp(weights.size(), vector<int>(bag + 1, 0));
    
        // 初始化, 因为需要用到dp[i - 1]的值
        // j < weight[0]已在上方被初始化为0
        // j >= weight[0]的值就初始化为value[0]
        for(int j=weights[0]; j<=bag; j++) {
            dp[0][j] = values[0];
        }

        for(int i=1; i<weights.size(); i++) {
            for(int j=1; j<=bag; j++) {
                if(weights[i] > j) {
                    dp[i][j] = dp[i-1][j];
                }
                else {
                    dp[i][j] = std::max(dp[i-1][j], dp[i-1][j-weights[i]] + values[i]);
                }
            }
        }
        return dp[weights.size() - 1][bag];
    }
};


// 16:50--16:58
// 背包问题，动态规划，一维数组
class Solution {
public:
    int solve(int bag, vector<int>& weights, vector<int>& value) {
        // 创建 dp 并初始化
        vector<int> dp(bag + 1, 0);
        for(int j=weights[0]; j<=bag; j++) {
            dp[j] = value[0];
        }
        for(int i=1; i<weights.size(); i++) {
            for(int j=1; j<=bag; j++) {
                if(j >= weights[i]) {
                    dp[j] = std::max(dp[j], dp[j-weights[i]] + value[i]);
                }
            }
        }
        return dp.back();
    }
};

class Solution_D2_copy {
public:
    int solve(int bag, vector<int>& weights, vector<int>& value) {
        // 创建 dp 并初始化
        vector<int> dp(bag + 1, 0);
        // 不用单独拿出来，放到 i = 0 中即可
        // for(int j=weights[0]; j<=bag; j++) {
        //     dp[j] = value[0];
        // }

        // 外层循环遍历每个类型的研究材料
        for(int i=0; i<weights.size(); i++) {
            // 内层循环从N空间逐渐减少到当前研究材料所占空间
            for(int j=bag; j>=weights[i]; j--) {
                dp[j] = std::max(dp[j], dp[j-weights[i]] + value[i]);   // 从后往前替换，否则前面的替换成更大的后，后面替换结果会变大
            }
        }
        return dp.back();
    }
};




int main() {
    int m = 0;
    int bag = 0;
    cin >> m;
    cin >> bag;
    vector<int> weights(m);
    vector<int> value(m);
    for(int i=0; i<m; i++) {
        cin >> weights[i];
    }
    for(int i=0; i<m; i++) {
        cin >> value[i];
    }
    
    Solution_D1 ss;
    std::cout << ss.solve(bag, weights, value);

    return 0;
}