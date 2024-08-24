// 59. 螺旋矩阵 II
// https://leetcode.cn/problems/spiral-matrix-ii/
// labuladong 题解
// 中等
// 给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。

// 示例 1：
// 输入：n = 3
// 输出：[[1,2,3],[8,9,4],[7,6,5]]

// 示例 2：
// 输入：n = 1
// 输出：[[1]]

// 提示：
// 1 <= n <= 20


#include <iostream>
#include <vector>
using namespace std;

// 59. 螺旋矩阵 II
// 给定一个正整数 n，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。
// 示例:
// 输入: 3 输出: [ [1, 2, 3], [ 8, 9, 4 ], [ 7, 6, 5 ] ]


// 底下的都不推荐，推荐参考 螺旋矩阵
// D:\Learning\Leetcode\21_2\3_54_spiral-matrix.cpp


vector<vector<int>> generateMatrix1(int n)
{
    vector<vector<int>> result(n, vector<int>(n, 0));
    int startx = 0, starty = 0; // 每一圈起始位置
    int num = 1;                // 每次赋的值
    int loop = n/2;             // 循环次数，n=3 时循环一圈，中间为(1,1)，n=4时循环两圈无中间位置
    int count;                  // 每次循环中每条边元素的个数
    for(int i=0; i<loop; i++)
    {
        count = n-1-2*i;        // 第一次为 n-1,后面依次递减 2,在循环中 count 只会大于 0
        for(int j=0; j<count; j++)
        {
            result[startx][starty++] = num++;   // 上
        }
        for(int j=0; j<count; j++)
        {
            result[startx++][starty] = num++;   // 右
        }
        for(int j=0; j<count; j++)
        {
            result[startx][starty--] = num++;   // 下
        }
        for(int j=0; j<count; j++)
        {
            result[startx--][starty] = num++;   // 左
        }
        startx++;           // 更新初试位置
        starty++;
    }

    if(n%2 == 1)    // n=1不进入循环时赋初值，n为奇数时矩阵中间没赋值
    {
        result[startx][starty] = num++; // 不管进没进循环，startx starty均指中间位置
    }

    return result;
}

vector<vector<int>> generateMatrix2(int n)
{
    vector<vector<int>> result(n, vector<int>(n, 0));
    int startx = 0, starty = 0;
    int endx = 0, endy = 0;
    int num1 = 1, num2=0, num3=0, num4=0;
    int loop = n/2;
    int count;
    for(int i=0; i<loop; i++)
    {
        count = n - 1 - 2 * i;
        num2 = num1 + count;
        num3 = num2 + count;
        num4 = num3 + count;
        for(int j=0; j<count; j++)
        {
            endx = startx + count;  // 对角线坐标
            endy = starty + count;
            result[startx][starty+j] = num1++;
            result[startx+j][endy] = num2++;
            result[endx][endy-j] = num3++;
            result[endx-j][starty] = num4++;
        }
        startx++;
        starty++;
        num1+=count*3;
    }
    if(n%2 == 1)
    {
        result[startx][starty] = num1;
    }
    return result;
}

#if 0
int main()
{
    int n=4;
    vector<vector<int>> M = generateMatrix2(n);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            cout << M[i][j] << "\t";
        cout << endl;
    }
}
#endif





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// 21:38--21:46(好多错误)--22:05
// dir 数组
class Solution_S2_M1 {
public:
    vector<vector<int>> generateMatrix(int n) {
        // 逆时针的四个方向顺序
        int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
        vector<vector<int>> result(n, vector<int>(n, 0));
        int max = n * n;
        int row = 0, col = 0, state = 0;
        result[0][0] = 1;           // 先填充       ***
        for(int i=2; i<=max; i++) { // 从 2 开始
            // 定位下一格
            row += dir[state][0];
            col += dir[state][1];
            // 需要换向
            // >= n
            if(row<0 || row>=n || col<0 || col>=n || result[row][col] != 0) { // ***
                row -= dir[state][0];   // 恢复
                col -= dir[state][1];
                state++;                // 换向
                state %= 4;
                row += dir[state][0];   // 重新定位
                col += dir[state][1];
            }
            // 填充
            result[row][col] = i;
        }
        return result;
    }
};

// M1 微调
class Solution_S2_M2 {
public:
    vector<vector<int>> generateMatrix(int n) {
        // 逆时针的四个方向顺序
        int dir[4][2] = {0, 1, 1, 0, 0, -1, -1, 0};
        vector<vector<int>> result(n, vector<int>(n, 0));
        int max = n * n;
        int row = 0, col = 0, state = 0;
        for(int i=1; i<=max; i++) { // 从 2 开始
            // 填充
            result[row][col] = i;
            // 定位下一格
            row += dir[state][0];
            col += dir[state][1];
            // 需要换向
            // >= n
            if(row<0 || row>=n || col<0 || col>=n || result[row][col] != 0) { // ***
                row -= dir[state][0];   // 恢复
                col -= dir[state][1];
                state++;                // 换向
                state %= 4;
                row += dir[state][0];   // 重新定位
                col += dir[state][1];
            }
        }
        return result;
    }
};


// 16:33--16:49--16:56(解决多处错误)
class Solution_S2_M3_L1 {
public:
    vector<vector<int>> generateMatrix(int n) {
        int up_lim = 0, down_lim = n - 1;
        int left_lim = 0, right_lim = n - 1;
        vector<vector<int>> result(n, vector<int>(n, 0));   // 没初始化 ***
        int num = 1;
        int max = n * n;    // 最大值未计算，直接用的 n     ***
        while(num <= max) {
            // 顶部从左往右遍历
            if(up_lim <= down_lim) {
                for(int j=left_lim; j<=right_lim; j++) {
                    result[up_lim][j] = num++;
                }
                // 上边界下移
                up_lim++;
            }
            // 右侧从上往下遍历
            if(left_lim <= right_lim) {
                for(int i=up_lim; i<=down_lim; i++) {
                    result[i][right_lim] = num++;
                }
                // 右边界左移
                right_lim--;
            }
            // 底部从右往左遍历
            if(up_lim <= down_lim) {
                for(int j=right_lim; j>=left_lim; j--) {
                    result[down_lim][j] = num++;
                }
                // 下边界上移
                down_lim--;
            }
            // 左侧从下往上遍历
            if(left_lim <= right_lim) {
                for(int i=down_lim; i>=up_lim; i--) {
                    result[i][left_lim] = num++;
                }
                // 左边界右移
                left_lim++;
            }
        }
        return result;
    }
};