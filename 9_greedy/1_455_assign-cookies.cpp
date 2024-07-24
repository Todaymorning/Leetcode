// 455. 分发饼干
// 简单
// 假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
// 对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，
// 我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。

// 示例 1:
// 输入: g = [1,2,3], s = [1,1]
// 输出: 1
// 解释: 
// 你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
// 虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
// 所以你应该输出1。

// 示例 2:
// 输入: g = [1,2], s = [1,2,3]
// 输出: 2
// 解释: 
// 你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
// 你拥有的饼干数量和尺寸都足以让所有孩子满足。
// 所以你应该输出2.
 

// 提示：
// 1 <= g.length <= 3 * 10^4
// 0 <= s.length <= 3 * 10^4
// 1 <= g[i], s[j] <= 2^31 - 1

#include<iostream>
#include<vector>
#include<algorithm>
using std::sort;
using std::vector;
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {

    }
};



// 10:19--10:37
// 为饼干找一个人：从大到小遍历
// 这里的局部最优就是大饼干喂给胃口大的，充分利用饼干尺寸喂饱一个，全局最优就是喂饱尽可能多的小孩。
// 从这里可以看出，最好从最大的开始遍历，才能充分利用好每个饼干
// 看过 D1 的思路后开写
// 时间复杂度：O (nlogn)
// 空间复杂度：O (1)
class Solution_D1_M1 {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int result = 0;
        int max_s = s.size() - 1;
        int max_g = g.size() - 1;
        // 先取一个饼干出来，找到一个可以喂饱的人后再取下一个饼干，如果喂不饱，找下一个人
        for(int i=max_g, j=max_s; i>=0 && j>=0; i--) {  // 拿到饼干后遍历每一个人，直到饼干被使用后再取下一块饼干
            if(s[j] >= g[i]) {  // 大饼干满足胃口
                result++;
                j--;    // 该饼干用了，取下一块饼干
            }
        }
        return result;
    }
};




// 10:39
// 为一个人找饼干：从小到大遍历
// 也可以换一个思路，小饼干先喂饱小胃口
// 看过 D2 的思路后开写
class Solution_D2_M2 {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int result = 0;
        int max_g = g.size();
        int max_s = s.size();
        // 取最小胃口的人开始从小到大遍历饼干，找到最小能满足胃口的饼干后再取下一个人
        for(int i=0, j=0; i<max_g && j<max_s; j++) {
            if(s[j] >= g[i]) {
                result++;
                i++;    // 为下一个人找饼干
            }
        }
        return result;
    }
};


