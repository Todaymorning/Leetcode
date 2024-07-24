// https://leetcode.cn/problems/spiral-matrix
// 54. 螺旋矩阵
// labuladong 题解
// 中等
// 相关标签
// 相关企业
// 提示
// 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

// 示例 1：
// 输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
// 输出：[1,2,3,6,9,8,7,4,5]

// 示例 2：
// 输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
// 输出：[1,2,3,4,8,12,11,10,9,5,6,7]

// 提示：
// m == matrix.length
// n == matrix[i].length
// 1 <= m, n <= 10
// -100 <= matrix[i][j] <= 100


#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {

    }
};


// 2024年4月30日
// 20:06--20:20
class Solution {
    int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<bool>> used(m, vector<bool>(n, false));
        vector<int> result(m*n);
        int flag = 0;
        int idx = 0;
        int x = 0, y=0;
        while(idx < m*n) {
            used[x][y] = true;
            result[idx++] = matrix[x][y];
            x += dir[flag%4][0];
            y += dir[flag%4][1];
            if(x < 0 || x >= m || y < 0 || y >= n || used[x][y]) {
                x -= dir[flag%4][0];
                y -= dir[flag%4][1];
                flag++;
                x += dir[flag%4][0];
                y += dir[flag%4][1];
            }
        }
        return result;
    }
};




// 2024年5月20日
// 19:45--20:05
// 四个循环模拟四个路径，变化上下左右限
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // [up, down], [left, right]
        int up = 0, down = matrix.size(), left = 0, right = matrix[0].size();
        int idx = 0, max = down * right, x = 0, y = 0;
        vector<int> result(max);
        right--, down--;
        while(idx < max) {
            // 从左到右
            if(up <= down) {    // 左右看上下界是否满足要求 ***
                for(int j=left; j<=right; j++) {
                    result[idx++] = matrix[up][j];
                }
                up++;
            }
            // 从上到下
            if(left <= right) { // ***
                for(int i=up; i<=down; i++) {
                    result[idx++] = matrix[i][right];
                }
                right--;
            }
            // 从右到左
            if(up <= down) {
                for(int j=right; j>=left; j--) {
                    result[idx++] = matrix[down][j];
                }
                down--;
            }
            // 从下到上
            if(left <= right) {
                for(int i=down; i>=up; i--) {
                    result[idx++] = matrix[i][left];
                }
                left++;
            }
        }
        return result;
    }
};