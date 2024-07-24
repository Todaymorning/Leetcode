// 134. 加油站
// 中等
// 在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
// 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
// 给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。

// 示例 1:
// 输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
// 输出: 3
// 解释:
// 从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
// 开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
// 开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
// 开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
// 开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
// 开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
// 因此，3 可为起始索引。

// 示例 2:
// 输入: gas = [2,3,4], cost = [3,4,3]
// 输出: -1
// 解释:
// 你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
// 我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
// 开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
// 开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
// 你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
// 因此，无论怎样，你都不可能绕环路行驶一周。

// 提示:
// gas.length == n
// cost.length == n
// 1 <= n <= 10^5
// 0 <= gas[i], cost[i] <= 10^4


#include<iostream>
#include<vector>
using std::vector;
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

    }
};

// 暴力解法
// 15:50--16:06(超出时间限制)--16:46
#if 0
class Solution_M1 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int result = -1;
        if((gas.size() < 1) || (gas.size() != cost.size())) return result;
        int size = gas.size();
        int sum = 0;
        int temp = 0;
        for(int i=0; i<size; i++) {
            result = i;         // 起始站点
            sum = 0;            // 剩余汽油
            for(int j=0; j<=size; j++) {
                if(sum < 0) {   // 汽油不够到下一站
                    result = -1;
                    break;
                }
                temp = (i+j)%size;
                sum = sum + gas[temp] - cost[temp]; // 到达下一站时汽油的余量
            }
            if(result != -1) break;
        }
        return result;
    }
};

// 暴力解法(超出时间限制)
// for 循环适合模拟从头到尾的遍历，而 while 循环适合模拟环形遍历，要善于使用 while！
// 时间复杂度：O (n^2)
// 空间复杂度：O (1)
class Solution_D1 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        if(gas.size() < 1 || (gas.size() != cost.size())) return -1;
        int size = gas.size();
        int res;
        int idx;
        for(int i=0; i<size; i++) {
            res = gas[i] - cost[i];
            idx = (i+1) % size;
            while(res > 0 && i != idx) {    // 模拟以i为起点行驶一圈（如果有rest==0，那么答案就不唯一了）
                res += gas[i] - cost[i];
                idx = (idx + 1) % size;
            }
            if(res >= 0 && i == idx) return i;
        }
        return -1;
    }
};



class Solution_D1_M2 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        if(gas.size() < 1 || (gas.size() != cost.size())) return -1;
        int size = gas.size();
        vector<int> gc(size, 0);
        for(int i=0; i<size; i++) {
            gc[i] = gas[i] - cost[i];
        }
        int res;
        int idx;
        for(int i=0; i<size; i++) {
            res = gc[i];
            idx = (i + 1) % size;
            while(res>0 && idx != i) {
                res += gc[idx];
                idx = (idx + 1) % size;
            }
            if(res >= 0 && i == idx) return i;
        }
        return -1;
    }
};
#endif


// 贪心算法（方法一）----非完整的贪心，没有局部最优
// 直接从全局进行贪心选择，情况如下：
// 情况一：如果 gas 的总和小于 cost 总和，那么无论从哪里出发，一定是跑不了一圈的
// 情况二：rest [i] = gas [i]-cost [i] 为一天剩下的油，i 从 0 开始计算累加到最后一站，如果累加没有出现负数，说明从 0 出发，油就没有断过，那么 0 就是起点。
// 情况三：如果累加的最小值是负数，汽车就要从非 0 节点出发，从后向前，看哪个节点能把这个负数填平，能把这个负数填平的节点就是出发节点。
// 16:53--17:18
// 查看 D2 的思路+代码后默写
// long long int：否则可能会溢出
// INT_MAX 而不是INT_MIN
// i-- 而不是 i++
class Solution_D2 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        long long int curSum = 0;     // ***
        long long int min = INT_MAX;  // 从第0个索引出发，邮箱里油量的最小值
        for(int i=0; i<gas.size(); i++) {
            curSum += gas[i] - cost[i];
            if(curSum < min) min = curSum;  // 记录从第0个数开始累加的最小值
        }
        if(curSum < 0) return -1;   // 情况一：汽油总量小于消耗量
        if(min >= 0) return 0;       // 情况二：从第0个开始累加没出现过负数
                                    // 情况三：
        for(int i=gas.size()-1; i>0; i--) { // ***
            min += gas[i] - cost[i];
            if(min >= 0) return i;
        }

        return -1;
    }
};

class Solution_D2_copy {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int min = INT_MAX; // 从起点出发，油箱里的油量最小值
        for (int i = 0; i < gas.size(); i++) {
            int rest = gas[i] - cost[i];
            curSum += rest;
            if (curSum < min) {
                min = curSum;
            }
        }
        if (curSum < 0) return -1;  // 情况1
        if (min >= 0) return 0;     // 情况2
                                    // 情况3
        for (int i = gas.size() - 1; i >= 0; i--) {
            int rest = gas[i] - cost[i];
            min += rest;
            if (min >= 0) {
                return i;
            }
        }
        return -1;
    }
};


// 如果总油量减去总消耗大于等于零那么一定可以跑完一圈，说明 各个站点的加油站 剩油量 rest [i] 相加一定是大于等于零的。
// 每个加油站的剩余量 rest [i] 为 gas [i] - cost [i]。
// i 从 0 开始累加 rest [i]，和记为 curSum，一旦 curSum 小于零，说明 [0, i] 区间都不能作为起始位置，因为这个区间选择任何一个位置作为起点，
// 到 i 这里都会断油，那么起始位置从 i+1 算起，再从 0 计算 curSum。
// 那么局部最优：当前累加 rest [i] 的和 curSum 一旦小于 0，起始位置至少要是 i+1，因为从 i 之前开始一定不行。全局最优：找到可以跑一圈的起始位置。
// 17:32--17:39
// 看过 D3 思路
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution_D3 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalSum = 0;   // 总的剩余油量
        int curSum = 0;     // 从idx开始的剩余油量
        int idx = 0;        // 累加起始位置
        int res = 0;
        for(int i=0; i<gas.size(); i++) {
            res = gas[i] - cost[i];
            totalSum += res;
            curSum += res;
            if(curSum < 0) {
                curSum = 0;
                idx = i + 1;
            }
        }
        if(totalSum < 0) return -1;
        return idx;
    }
};
