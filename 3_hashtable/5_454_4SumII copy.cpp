// 第 454 题。四数相加 II
// 给定四个包含整数的数组列表 A , B , C , D , 计算有多少个元组 (i, j, k, l) ，
// 使得 A [i] + B [j] + C [k] + D [l] = 0。
// 为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且 0 ≤ N ≤ 500 。
// 所有整数的范围在 -2^28 到 2^28 - 1 之间，最终结果不会超过 2^31 - 1 。

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 思路与算法
// 我们可以将四个数组分成两部分,A和 B为一组,C和 D为另外一组.
// 对于A和 B,使用二重循环遍历,得到所有A[i]+B[j]的值并存入哈希映射中.
// 每个 key 表示一种 A[i]+B[j],对应的 value 为A[i]+B[j]出现的次数.
// 对于C和 D,我们同样使用二重循环对它们进行遍历.当遍历到C[k]+D[l]时,如果
// -(C[k]] +D[l])出现在哈希映射中,那么将-(C[k] + D[l])对应的值累加进答案中.
// 最终即可得到满足A[i] +B[j] +C[k] + D[1] = 0的四元组数目.
// 复杂度分析
// . 时间复杂度:O(n^2).我们使用了两次二重循环,时间复杂度均为O(n^2).
// 在循环中对哈希映射进行的修改以及查询操作的期望时间复杂度均为O(1),因此总时间复杂度为 O(n^2)
// ·空间复杂度:O(n^2),即为哈希映射需要使用的空间.在最坏的情况下, A[]+B[j]的值
// 均不相同,因此值的个数为 n^2,也就需要O(n^2)的空间.
int fourSumCount_G1(vector<int> & nums1, vector<int> & nums2, 
                vector<int> & nums3, vector<int> & nums4)
{
    unordered_map<int,int> sumAB;   // key 为元素和， value为个数
    for(int i:nums1)
    {
        for(int j:nums2)
        {
            sumAB[i+j]++;
        }
    }
    int count = 0;
    for(int i:nums3)
    {
        for(int j:nums4)
        {
            if(sumAB.count(0-i-j))  // sumAB.find(0-i-j) != sumAB.end()
            {
                count += sumAB[0-i-j];   // m*n 的排列组合
            }
        }
    }
    return count;
}