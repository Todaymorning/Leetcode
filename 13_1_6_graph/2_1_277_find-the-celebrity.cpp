// 277. 搜寻名人
// https://leetcode.cn/problems/find-the-celebrity
// 中等
// 提示
// 假设你是一个专业的狗仔，参加了一个 n 人派对，其中每个人被从 0 到 n - 1 标号。在这个派对人群当中可能存在一位 “名人”。
// 所谓 “名人” 的定义是：其他所有 n - 1 个人都认识他/她，而他/她并不认识其他任何人。
// 现在你想要确认这个 “名人” 是谁，或者确定这里没有 “名人”。而你唯一能做的就是问诸如 “A 你好呀，请问你认不认识 B呀？” 的问题，
// 以确定 A 是否认识 B。你需要在（渐近意义上）尽可能少的问题内来确定这位 “名人” 是谁（或者确定这里没有 “名人”）。
// 在本题中，你可以使用辅助函数 bool knows(a, b) 获取到 A 是否认识 B。请你来实现一个函数 int findCelebrity(n)。
// 派对最多只会有一个 “名人” 参加。若 “名人” 存在，请返回他/她的编号；若 “名人” 不存在，请返回 -1。

// 示例 1:
// 输入: graph = [
//   [1,1,0],
//   [0,1,0],
//   [1,1,1]
// ]
// 输出: 1
// 解释: 有编号分别为 0、1 和 2 的三个人。graph[i][j] = 1 代表编号为 i 的人认识编号为 j 的人，
// 而 graph[i][j] = 0 则代表编号为 i 的人不认识编号为 j 的人。“名人” 是编号 1 的人，因为 0 和 2 均认识他/她，但 1 不认识任何人。

// 示例 2:
// 输入: graph = [
//   [1,0,1],
//   [1,1,0],
//   [0,1,1]
// ]
// 输出: -1
// 解释: 没有 “名人”

// 提示：
//     n == graph.length
//     n == graph[i].length
//     2 <= n <= 100
//     graph[i][j] 是 0 或 1.
//     graph[i][i] == 1

// 进阶：如果允许调用 API knows 的最大次数为 3 * n ，你可以设计一个不超过最大调用次数的解决方案吗？



#include<iostream>
#include<queue>
using std::queue;


/* The knows API is defined for you.
      bool knows(int a, int b); */
bool knows(int a, int b) {
    return true;    // 返回 a 是否认识 b
}

class Solution {
public:
    int findCelebrity(int n) {
        
    }
};


// 暴力解法：一层循环选择候选人，一层循环负责判断
class Solution_L1_M1 {
public:
    int findCelebrity(int n) {
        for(int cand=0; cand<n; cand++) {   // 候选人
            int other;
            for(other=0; other<n; other++) {    // 判断是否满足条件
                if(cand == other) continue;     // 自己跟自己不判断
                // 保证cand不认识其他人且被其他所有人认识
                if(knows(cand, other) || !knows(other, cand)) { 
                    break;  // 只要cand认识任何一个other，或不被任何一个other认识，找下一个候选人
                }
            }
            if(other == n) {    // 找到
                return cand;
            }
        }
        return -1;  // 没找到
    }
};

// 16:34(看完L1思路)--17:05
// 至多只有一个
// 只要观察任意两个候选人的关系，我一定能确定其中的一个人不是名人，把他排除。
// 情况一，cand 认识 other，所以 cand 肯定不是名人，排除。因为名人不可能认识别人。
// 情况二，other 认识 cand，所以 other 肯定不是名人，排除。
// 情况三，他俩互相认识，肯定都不是名人，可以随便排除一个。
// 情况四，他俩互不认识，肯定都不是名人，可以随便排除一个。因为名人应该被所有其他人认识。
// 我们可以不断从候选人中选两个出来，然后排除掉一个，直到最后只剩下一个候选人，
// 这时候再使用一个 for 循环判断这个候选人是否是货真价实的「名人」。
// 使用队列
class Solution_L2_M2 {
public:
    int findCelebrity(int n) {
        queue<int> q;
        // 所有候选人入列
        for(int i=0; i<n; i++) q.push(i);
        // 排除，直到剩余一个
        while(q.size() > 1) {
            int cand = q.front(); q.pop();
            int other = q.front(); q.pop();
            if(knows(cand, other) || !knows(other, cand)) {   // cand 不可能是
                q.push(other);
            }
            else {
                q.push(cand);   // other 不可能是
            }
        }
        // 只剩一个，判断是否是名人
        int cand = q.front(); q.pop();
        for(int other=0; other<n; other++) {
            if(cand == other) continue;
            if(knows(cand, other) || !knows(other, cand)) { // ***
                return -1;
            }
        }
        return cand;
    }
};

// 不使用额外空间
class Solution_L3_M3 {
public:
    int findCelebrity(int n) {
        int cand = 0;
        int other = 1;
        while(other < n) {
            if(knows(cand, other) || !knows(other, cand)) {
                cand = other;   // cand 不可能是，抛弃 cand
                other++;
            }
            else {
                other++;    // other 不可能是，抛弃 other
            }
        }
        for(other=0; other<n; other++) {
            if(cand == other) continue;     // ***
            if(knows(cand, other) || !knows(other, cand)) {
                return -1;
            }
        }
        return cand;
    }
};

