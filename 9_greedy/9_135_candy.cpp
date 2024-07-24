// 135. 分发糖果
// 困难
// n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。
// 你需要按照以下要求，给这些孩子分发糖果：
// 每个孩子至少分配到 1 个糖果。
// 相邻两个孩子评分更高的孩子会获得更多的糖果。
// 请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。

// 示例 1：
// 输入：ratings = [1,0,2]
// 输出：5
// 解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
// 示例 2：
// 输入：ratings = [1,2,2]
// 输出：4
// 解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
//      第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。

// 提示：
// n == ratings.length
// 1 <= n <= 2 * 10^4
// 0 <= ratings[i] <= 2 * 10^4


#include<iostream>
#include<vector>
using std::vector;
class Solution {
public:
    int candy(vector<int>& ratings) {

    }
};


// 19:31--20:01(不会)
// 先确定右边评分大于左边的情况（也就是从前向后遍历）
// 此时局部最优：只要右边评分比左边大，右边的孩子就多一个糖果，全局最优：相邻的孩子中，评分高的右孩子获得比左边孩子更多的糖果
// 局部最优可以推出全局最优。
// 再确定左孩子大于右孩子的情况（从后向前遍历）
// 20:08--20:13--20:24
// 看过 D1的思路
// 时间复杂度: O (n)
// 空间复杂度: O (n)
class Solution_D1 {
public:
    int candy(vector<int>& ratings) {
        int size = ratings.size();
        if(size < 2) return 1;
        vector<int> results(size, 1);
        // 从前往后，右边大时，右边 是 左边加一
        for(int i=0; i<size-1; i++) {
            if(ratings[i+1] > ratings[i]) results[i+1] = results[i] + 1;    // ***
        }
        // 从后往前，左边大时，左边是其 本身 和 右边加一 的最大值
        for(int i=size-1; i>0; i--) {
            if(ratings[i-1] > ratings[i]) results[i-1] = (results[i]+1) > results[i-1] ? (results[i] + 1) : results[i-1]; // ***
        }
        // 统计结果
        int result = 0;
        for(int i=0; i<size; i++) result += results[i];
        return result;
    }
};



// 我们从左到右枚举每一个同学，记前一个同学分得的糖果数量为 pre
// 如果当前同学比上一个同学评分高，说明我们就在最近的递增序列中，直接分配给该同学 pre+1 个糖果即可。
// 否则我们就在一个递减序列中，我们直接分配给当前同学一个糖果，并把该同学所在的递减序列中所有的同学都再多分配一个糖果，以保证糖果数量还是满足条件。
// 我们无需显式地额外分配糖果，只需要记录当前的递减序列长度，即可知道需要额外分配的糖果数量。
// 同时注意当当前的递减序列长度和上一个递增序列等长时，需要把最近的递增序列的最后一个同学也并进递减序列中。
// 这样，我们只要记录当前递减序列的长度 dec ，最近的递增序列的长度 inc 和前一个同学分得的糖果数量 pre 即可。
// 时间复杂度: O (n)
// 空间复杂度: O (1)
class Solution_G2 {
public:
    int candy(vector<int>& ratings) {
        int inc = 1;
        int dec = 0;
        int pre = 1;
        int result = 1;
        for(int i=1; i<ratings.size(); i++) {
            // 处于递增序列
            if(ratings[i] >= ratings[i-1]) {
                dec = 0;    // 递减清零
                pre = ratings[i] == ratings[i-1] ? 1 : pre + 1; //当前同学和上一个同学分数相等时，直接分配1个就行，这样满足最小
                result += pre;
                inc = pre;  // 记录上一个递增序列的长度，前面一有相等的就变 1
            }
            else {  // 处于递减序列
                dec++;              // 从 1 开始累加，相当于把递减序列翻转后编程递增序列
                if(dec == inc) {    // 当递减序列长度和递增序列长度相等时，把递增序列的最后一个同学分配到递减序列中
                    dec++;          // 递增序列的最后一个（最大一个）编程递减序列的一部分，需要抬高
                }
                result += dec;  // 这里加的dec相当于把递减序列翻转后加的每个同学的糖果数量
                pre = 1;        // pre在递减序列中没有意义，因为我肯定比前一个同学少；
            }
        }
        return result;
    }
};