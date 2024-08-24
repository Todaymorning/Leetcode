// https://leetcode.cn/problems/set-matrix-zeroes/solutions/669901/ju-zhen-zhi-ling-by-leetcode-solution-9ll7/?envType=study-plan-v2&envId=top-100-liked
// 73. 矩阵置零
// 已解答
// 中等
// 相关标签
// 相关企业
// 提示
// 给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

 

// 示例 1：


// 输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
// 输出：[[1,0,1],[0,0,0],[1,0,1]]
// 示例 2：


// 输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
// 输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 

// 提示：

// m == matrix.length
// n == matrix[0].length
// 1 <= m, n <= 200
// -231 <= matrix[i][j] <= 231 - 1
 

// 进阶：

// 一个直观的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
// 一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
// 你能想出一个仅使用常量空间的解决方案吗？



#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {

    }
};


// 可以用两个标记数组分别记录每一行和每一列是否有零出现。
// 首先遍历该数组一次，如果某个元素为 0，那么就将该元素所在的行和列所对应标记数组
// 的位置置为 true。最后我们再次遍历该数组，用标记数组更新原数组即可。
class Solution_G1 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> row(m), col(n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!matrix[i][j]) {    // 某个元素为 0，标记改行该列
                    row[i] = col[j] = true;
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (row[i] || col[j]) { // 行或列中有一个元素为 0
                    matrix[i][j] = 0;
                }
            }
        }
    }
};


// 我们可以用矩阵的第一行和第一列代替方法一中的两个标记数组，以达到 O(1) 的额外空间。
// 但这样会导致原数组的第一行和第一列被修改，无法记录它们是否原本包含 0。
// 因此我们需要额外使用两个标记变量分别记录第一行和第一列是否原本包含 0。

// 首先预处理出两个标记变量，接着使用其他行与列去处理第一行与第一列，
// 然后反过来使用第一行与第一列去更新其他行与列，最后使用两个标记变量更新第一行与第一列即可。
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int flag_col0 = false, flag_row0 = false;
        for (int i = 0; i < m; i++) {
            if (!matrix[i][0]) {
                flag_col0 = true;   // 统计第 0 列有没有 0
            }
        }
        for (int j = 0; j < n; j++) {
            if (!matrix[0][j]) {
                flag_row0 = true;   // 统计第 0 行有没有 0
            }
        }
        for (int i = 1; i < m; i++) {       // 从 1 开始
            for (int j = 1; j < n; j++) {
                if (!matrix[i][j]) {
                    matrix[i][0] = matrix[0][j] = 0;    // 中间元素为 0，在第 0 行和第 0 列做上标记
                }
            }
        }
        for (int i = 1; i < m; i++) {   // 从 1 开始
            for (int j = 1; j < n; j++) {
                if (!matrix[i][0] || !matrix[0][j]) {   // 根据标记处理中间
                    matrix[i][j] = 0;
                }
            }
        }
        if (flag_col0) {    // 第 0 列有 0
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
        if (flag_row0) {    // 第 0 行有 0
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }
    }
};